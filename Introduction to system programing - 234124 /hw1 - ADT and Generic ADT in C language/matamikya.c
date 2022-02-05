
#include "amount_set.h"
#include "matamikya.h"
#include "set.h"
#include "matamikya_print.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define POSITIVE 1
#define NEGATIVE -1
#define EQUAL 0
#define INTEGER_LIMIT 0.001
#define UPPER_HALF_INTEGER_LIMIT 0.501
#define LOWER_HALF_INTEGER_LIMIT 0.499



struct  Matamikya_t {
    AmountSet warehouse;
    Set orders ;
};

typedef struct ProductData_t {
    unsigned int Id ;
    char* Name ;
    MtmProductData  custom_data;
    MatamikyaAmountType amount_type ;
    MtmCopyData productCopyFunction;
    MtmFreeData productFreeFunction;
    MtmGetProductPrice getProductPriceFunc;
    double total_sold;
}
*ProductData;

typedef struct Order_t{
    unsigned int order_id;
    AmountSet order_data;
}*Order;


/* Static function used in matamikya */

/* strCopy
 * copy a string return NULL if not success and the string either , using a dynamic allocation
 * */

static char* strCopy (const char* element) // used in createdProductData , copyProductData
{
    size_t len_of_new_element=(strlen(element))+1;
    char* element_copy= malloc(sizeof(*element_copy)*len_of_new_element);
   element_copy=strcpy(element_copy,element);
    return element_copy ;
}
/* checkValidName : 
 * Check if the name is valid by the criterion of first letter starts with 0-9 or a-z or A-Z and the string not empty  *
  return true if the name is valid and false either . */
static bool checkValidName (const char* name) // used in mtmNewProduct
{
    if (((name[0] >= 'a' && name[0] <='z' ) || (name[0] >= 'A' && name[0] <='Z' ) || (name[0] >= '0' && name[0] <='9' )) && strcmp(name,"")!=0 ) return true;
    return false ;
}
/* checkAmountType
 * check if the amount is valid .
 * if its integer amount the amount can be between (int-1).99 to int.001
 * if its half integer amount the amount can be between (int-1).99 to int.001 or int.499 to int.501
 * */
static bool checkAmountType (const double amount ,const MatamikyaAmountType amountType ) {
    double amount_diff;
    double rounded_amount = (int)(amount+0.5);
    if (amount >= rounded_amount) amount_diff = amount - rounded_amount;
    else if (amount < rounded_amount) amount_diff = rounded_amount - amount;
    if (amountType == MATAMIKYA_INTEGER_AMOUNT)
    {
        if (amount_diff <= INTEGER_LIMIT && amount_diff >= EQUAL) return true;
        else return false;
}
    if (amountType == MATAMIKYA_HALF_INTEGER_AMOUNT )
    {
        if ( (amount_diff <= INTEGER_LIMIT && amount_diff >= EQUAL) || (amount_diff >= LOWER_HALF_INTEGER_LIMIT && amount_diff <= UPPER_HALF_INTEGER_LIMIT) )  return true ;
        else return false;
        }
    return true ;
}
/* getProductFromAmontSet
 * get an AmountSet and id and bring back the ASElmenet of the product that have the Id .
 * */
static ASElement getProductFromAmountSet (AmountSet warehouse , const unsigned int Id)
{
   AS_FOREACH(ASElement , element , warehouse)
    {
        if( ((ProductData)element)->Id == Id )
            return element ;
    }
    return NULL ;

}

/* getLastOrderId */
/* Function that help to get the last id in current orders list ;
 get the set of the orders and bring back the id .
 if the set is null brings back 0 and if the set is empty bring back 0 ; */

static unsigned int getLastOrderId(Set orders) {
    if (orders == NULL)
    {
        return 0;
    }
    unsigned int last_id = 0;
    SET_FOREACH (SetElement , element , orders  )  last_id=(*(Order)element).order_id ;
    return last_id+1;
}

/* findOrder */
/* Function that help to get the Set element of an order in the list we look for  ;
 get the set of the orders and the id of the order we look for and bring back the Set element of that order ;
 if the set is null brings back or if the set is empty bring back NULL either the SetElement  ; */

static SetElement findOrder (Set orders_list , unsigned int id)
    {
    if(orders_list == NULL) return NULL ;
        SET_FOREACH (SetElement , element , orders_list)
        {
            if( (*(Order)element).order_id==id) return element;
        }
        return NULL ;
    }

/* End for static function for matamikya */

/* Functions for ADT Product Data */

static ProductData createProductData (
                           const unsigned int id,
                           const char *name,
                           const MatamikyaAmountType amountType,
                           const MtmProductData customData,
                           MtmCopyData copyData,
                           MtmFreeData freeData,
                           MtmGetProductPrice prodPrice)

{
    if(name==NULL || customData==NULL || copyData==NULL || freeData==NULL || prodPrice == NULL ) return NULL;
    ProductData product = malloc(sizeof(*product));
    if(product == NULL )
    {
        return NULL ;
    }
    product-> Id = id;
    product->Name= strCopy(name);
    if(product->Name == NULL )
    {
        free(product) ;
        return NULL ;
    }
    product->custom_data = copyData(customData) ;
    if(product->custom_data == NULL)
    {
        free(product->Name);
        free(product);
        return NULL ;
    }
    product ->amount_type = amountType ;
    product->productCopyFunction = copyData;
    product->productFreeFunction = freeData;
    product-> getProductPriceFunc = prodPrice ;
    product->total_sold=0;
    return product;
}

static ProductData copyProductData(ProductData element)
{
    if(element == NULL )
    {
        return NULL;
    }
    ProductData new_element = malloc(sizeof(*new_element));
    if(new_element==NULL)
    {
        return NULL;
    }
    new_element -> Id = element -> Id;
    new_element -> Name = strCopy(element->Name);
    if(new_element->Name==NULL) {
        free(new_element);
        return NULL ;
    }
    new_element -> custom_data = (element->productCopyFunction(element->custom_data));
    if(new_element->custom_data == NULL) {
        free(new_element->Name);
        free(new_element);
        return NULL;
    }
    new_element -> amount_type = element->amount_type;
    new_element->total_sold = element -> total_sold;
    new_element -> productCopyFunction = element->productCopyFunction;
    new_element -> productFreeFunction = element->productFreeFunction;
    new_element -> getProductPriceFunc = element->getProductPriceFunc;
    return new_element ;
}
static void destroyProductData(ProductData element)
{
    if(element->custom_data != NULL )
    {
        element->productFreeFunction((element->custom_data));
    }
    if( element->Name != NULL )
    {
        free (element->Name);
    }
    free (element);
}
int compareProductData(ProductData element1 , ProductData element2)
{
    if(element1 == NULL)
    {
        if(element2 !=NULL )
        {
            return NEGATIVE;
        }
        else return EQUAL;
    }
    if(element2==NULL)
    {
        return POSITIVE;
    }
        if ( element1->Id > element2->Id )
        {
            return POSITIVE;
        }
        if ( element2->Id > element1->Id)
        {
            return NEGATIVE;
        }
        return (int)EQUAL;

}


/*End Of Functions for ADT Product Data */

/* Function for Adt Order */
static Order  copyOrder(Order order)
{
    if (order == NULL)
    {
        return NULL;
    }
    Order new_order = malloc(sizeof(*new_order));
    if (new_order == NULL)
    {
        return NULL;
    }
    new_order->order_data = asCopy(order->order_data);
    if (new_order->order_data == NULL) {
        free(order);
        return NULL;
    }
    new_order->order_id = order->order_id;
    return new_order;
}

static void freeOrder(Order order) {
    if (order == NULL)
    {
        return;
    }
    if (order->order_data == NULL) {
        free(order);
        return;
    }
    asDestroy(order->order_data);
    free(order);
}

static int compareOrders(Order order1, Order order2) {
    assert(order1 != NULL && order2 != NULL);
    if (order1->order_id > order2->order_id )
    {
        return POSITIVE;
    }
    if (order2->order_id > order1->order_id)
    {
        return NEGATIVE;
    }
    return EQUAL;
}

/*End For Order ADT Function */


/* Function for using the AmountSet ADT - ASElement points to ProductData ADT */

static ASElement copyProductDataToASElement (ASElement element)
{
    if(element==NULL)
    {
        return NULL ;
    }
    return (ASElement )copyProductData((ProductData) element);
}
static void freeProductDataToASElement (ASElement element)
{
    if (element == NULL )
    {
        return ;
    }
    destroyProductData((ProductData)element);
}

static int compareProductDataToASElement(ASElement element1 , ASElement element2)
{
return compareProductData((ProductData) element1, (ProductData) element2);
}

/* End of Function for using the AmountSet ADT - ASElement points to ProductData */

/* Function for using the Set Adt - SetElement points to Order ADT */

static SetElement setCopyForOrderElementData(SetElement element) {
    if(element==NULL)
    {
        return NULL;
    }
    SetElement copy_element = copyOrder((Order) element);
    return copy_element;
}
static void setDestroyForOrder (SetElement order)
{
    if(order==NULL)
    {
        return ;
    }
    freeOrder( (Order)order );
}
static int setOrdersCompare (SetElement order1 , SetElement order2 )
{
    int result = compareOrders((Order) order1, (Order) order2);
    return result ;
}

/* End of function required to create a set */

Matamikya matamikyaCreate()
{

    Matamikya matamikya = malloc(sizeof(*matamikya))  ;
    if(matamikya == NULL){
    return NULL ;
    }
    matamikya->warehouse = asCreate(copyProductDataToASElement, freeProductDataToASElement,compareProductDataToASElement);
    assert(matamikya->warehouse != NULL);
    if(matamikya->warehouse == NULL ){
        free(matamikya);
        return NULL ;
    }
    matamikya->orders= setCreate(setCopyForOrderElementData,setDestroyForOrder,setOrdersCompare);
    assert(matamikya->orders != NULL);
    if( matamikya->orders==NULL)
    {
        asDestroy(matamikya->warehouse);
        free(matamikya);
        return NULL ;
    }

        return matamikya;
}
void matamikyaDestroy(Matamikya matamikya)
{
    if(matamikya->warehouse != NULL) asDestroy(matamikya->warehouse);
    if(matamikya->orders != NULL) setDestroy(matamikya->orders);
    free(matamikya);
}
MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData , MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice)
{
    if(matamikya == NULL || matamikya->warehouse==NULL || name==NULL || customData==NULL || copyData==NULL || freeData==NULL || prodPrice == NULL  )
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if ( !checkValidName(name) )
    {
        return MATAMIKYA_INVALID_NAME;
    }
    if(!checkAmountType(amount,amountType) || amount < 0 )
    {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    ProductData new_data  ;
    if ( ( new_data = createProductData(id, name, amountType, customData, copyData, freeData, prodPrice) )== NULL )
    {
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    AmountSetResult registerResult = asRegister(matamikya->warehouse, (ASElement)new_data);
    if(registerResult==AS_OUT_OF_MEMORY)
    {
        destroyProductData(new_data);
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    if(registerResult == AS_ITEM_ALREADY_EXISTS )
    {
        destroyProductData(new_data);
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    if(registerResult==AS_SUCCESS)
    {
        destroyProductData(new_data);
        ASElement found = getProductFromAmountSet(matamikya->warehouse, id);
    AmountSetResult amount_result = asChangeAmount(matamikya->warehouse, found , amount);
    if(amount_result == AS_NULL_ARGUMENT) {
        asDelete(matamikya->warehouse, found) ;
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    }
    return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount)
{
   if ( matamikya==NULL || matamikya->warehouse==NULL)
   {
       return MATAMIKYA_NULL_ARGUMENT;
   }
    ASElement found = getProductFromAmountSet(matamikya->warehouse, id);
    if (found == NULL)
    {
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    double current_amount=0;
    asGetAmount(matamikya->warehouse,found,&current_amount);
    MatamikyaAmountType product_type = (*(ProductData)found).amount_type;
    if( (amount+current_amount < 0 ))
    {
        return MATAMIKYA_INSUFFICIENT_AMOUNT;
    }
    if(!checkAmountType(amount+current_amount,product_type) )
    {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (amount > 0) {
        if (!checkAmountType(amount, product_type)) {
            return MATAMIKYA_INVALID_AMOUNT;
        }
    }
    else {
        if (!checkAmountType(NEGATIVE * amount, product_type)) {
            return MATAMIKYA_INVALID_AMOUNT;
        }
    }
   AmountSetResult changing_result = asChangeAmount(matamikya->warehouse,found,amount);
  assert(changing_result==AS_SUCCESS);
   return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id) {
    if (matamikya == NULL || matamikya->warehouse == NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    ASElement found = getProductFromAmountSet(matamikya->warehouse, id);
    if (found == NULL)
    {
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    if(matamikya->orders != NULL) {
        SET_FOREACH(SetElement, element, matamikya->orders) {
            Order current_order = (Order) element;
                asDelete(current_order->order_data, found);
        }
        asDelete(matamikya->warehouse, found);
    }
    return MATAMIKYA_SUCCESS;
}

unsigned int mtmCreateNewOrder(Matamikya matamikya)
    {
        if(matamikya==NULL) return 0;
        if(matamikya->orders == NULL) return 0;
        Set orders_list = matamikya->orders ; // Didnt check for NULL because of setAdd ;
        Order new_order = malloc(sizeof(*new_order));
        if(new_order==NULL) return 0;
        unsigned int new_id = getLastOrderId(orders_list);
        new_order->order_id=new_id;
        new_order->order_data= asCreate(copyProductDataToASElement,freeProductDataToASElement,compareProductDataToASElement);
            if(setAdd(orders_list,(SetElement)new_order)==SET_SUCCESS) {
                asDestroy(new_order->order_data);
                free(new_order) ;
                return new_id;
        }
        asDestroy(new_order->order_data);
            free(new_order) ;
            return 0 ;
    }

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int
orderId, const unsigned int productId, const double amount){
    if(matamikya == NULL) return MATAMIKYA_NULL_ARGUMENT;
    Set orders_list = matamikya->orders;
    AmountSet warehouse = matamikya->warehouse;
    if( !warehouse ) return MATAMIKYA_NULL_ARGUMENT;
    if( !orders_list) return MATAMIKYA_ORDER_NOT_EXIST;
    if (amount==0) return MATAMIKYA_SUCCESS;
   Order found_order = (Order) findOrder(orders_list, orderId);
   if(found_order==NULL) return MATAMIKYA_ORDER_NOT_EXIST;
    AmountSet found_order_data = found_order->order_data;
    ASElement product = getProductFromAmountSet(found_order_data, productId);

            if (product == NULL) { // This is the adding part
                if(amount>0) {
                    ASElement product_to_add = getProductFromAmountSet(warehouse, productId);
                    if( product_to_add == NULL ) return MATAMIKYA_PRODUCT_NOT_EXIST;
                    if (!checkAmountType(amount , (*(ProductData)product_to_add).amount_type)) return MATAMIKYA_INVALID_AMOUNT ;
                    AmountSetResult register_result = asRegister(found_order_data, product_to_add);
                    assert(register_result != AS_NULL_ARGUMENT);
                    if (register_result == AS_OUT_OF_MEMORY)return MATAMIKYA_OUT_OF_MEMORY;
                  asChangeAmount(found_order_data, product_to_add, amount);
                  return MATAMIKYA_SUCCESS;
                }
                else {
                    ASElement product_to_add = getProductFromAmountSet(warehouse, productId);
                    if( product_to_add == NULL ) return MATAMIKYA_PRODUCT_NOT_EXIST;
                    if (!checkAmountType(NEGATIVE*amount , (*(ProductData)product_to_add).amount_type)) return MATAMIKYA_INVALID_AMOUNT ;
                    return MATAMIKYA_SUCCESS;
                }
            }
            if (amount > 0) {
                if (!checkAmountType(amount, (*(ProductData) product).amount_type)) return MATAMIKYA_INVALID_AMOUNT;
            }
            else {
                if (!checkAmountType(NEGATIVE*amount, (*(ProductData) product).amount_type)) return MATAMIKYA_INVALID_AMOUNT;
            }
            double current_amount=0 ;
            asGetAmount(found_order_data,product,&current_amount);
            if(current_amount+amount <= 0) {
             asDelete(found_order_data,product);
             return MATAMIKYA_SUCCESS;
           }
    if (!checkAmountType(amount+current_amount, (*(ProductData) product).amount_type)) return MATAMIKYA_INVALID_AMOUNT;
            AmountSetResult change_amount_result = asChangeAmount(found_order_data, product, amount);
            assert(change_amount_result==AS_SUCCESS);
            return MATAMIKYA_SUCCESS;
        }

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int
orderId){
    if(matamikya == NULL) return MATAMIKYA_NULL_ARGUMENT;
    Set orders_list = matamikya->orders;
    if(orders_list == NULL) return MATAMIKYA_ORDER_NOT_EXIST;
    Order found_order =(Order) findOrder(orders_list, orderId);
    if(found_order == NULL) return MATAMIKYA_ORDER_NOT_EXIST;
    AmountSet warehouse = matamikya->warehouse;
    AmountSet found_order_data = found_order->order_data;
    ASElement current_item = asGetFirst(found_order_data);
    double amount_in_order = 0, amount_in_storage =0;
    while(current_item != NULL){
        ASElement product_in_warehouse = getProductFromAmountSet(warehouse,((ProductData)current_item)->Id);
        asGetAmount(warehouse,product_in_warehouse,&amount_in_storage);
        asGetAmount(found_order_data, current_item, &amount_in_order);
        if(amount_in_order > amount_in_storage)
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        current_item = asGetNext(found_order_data);
    }
    current_item = asGetFirst(found_order_data);
    while(current_item != NULL){
        ASElement product_in_warehouse = getProductFromAmountSet(warehouse,((ProductData)current_item)->Id);
        asGetAmount(warehouse,product_in_warehouse,&amount_in_storage);
        asGetAmount(found_order_data, current_item, &amount_in_order);
        ((ProductData)(product_in_warehouse))->total_sold += ((ProductData)product_in_warehouse)->getProductPriceFunc( (*(ProductData)product_in_warehouse).custom_data , amount_in_order);
        asChangeAmount(warehouse,product_in_warehouse,-amount_in_order);
        current_item = asGetNext(found_order_data);
    }
    setRemove(orders_list, found_order);
    return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int
orderId){
    if(matamikya == NULL) return MATAMIKYA_NULL_ARGUMENT;
    Set orders = matamikya->orders;
    if(orders == NULL) return MATAMIKYA_ORDER_NOT_EXIST;
    SetElement found_order = findOrder(orders,orderId);
    if(found_order == NULL) return MATAMIKYA_ORDER_NOT_EXIST;
  //  asDestroy((*(Order)found_order).order_data);
    SetResult result = setRemove(orders,found_order);
    if(result != SET_SUCCESS) return MATAMIKYA_ORDER_NOT_EXIST;
    return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output)
{
   if(matamikya==NULL || output==NULL ) return MATAMIKYA_NULL_ARGUMENT;
   fprintf(output,"Inventory Status:\n");
   if(matamikya->warehouse==NULL) return MATAMIKYA_SUCCESS;
   AmountSet warehouse = matamikya->warehouse ;
    AS_FOREACH(ASElement , element , warehouse)
    {
        double amount=0;
        asGetAmount(warehouse,element,&amount);
        mtmPrintProductDetails((*(ProductData)element).Name , (*(ProductData)element).Id,amount,(*(ProductData)element).getProductPriceFunc((*(ProductData)element).custom_data , 1 ) , output );
    }
return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output)
{
    if(matamikya == NULL || output==NULL) return MATAMIKYA_NULL_ARGUMENT ;
    if(matamikya->orders == NULL ) return MATAMIKYA_ORDER_NOT_EXIST;
    Set orders = matamikya->orders ;
    SetElement order_to_print = findOrder(orders, orderId );
    if(order_to_print==NULL) return MATAMIKYA_ORDER_NOT_EXIST;
    mtmPrintOrderHeading( (*(Order)order_to_print).order_id,output);
    double total_order_price=0;
    AmountSet order_data_to_print = (*(Order)order_to_print).order_data ;
    AS_FOREACH(ASElement , element , order_data_to_print) {
        double amount = 0;
        asGetAmount(order_data_to_print, element, &amount);
            double total_product_price = (*(ProductData) element).getProductPriceFunc((*(ProductData) element).custom_data, amount);
            mtmPrintProductDetails((*(ProductData) element).Name, (*(ProductData) element).Id, amount, total_product_price, output);
        total_order_price += total_product_price ;

    }
    mtmPrintOrderSummary(total_order_price, output);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output){
    if(matamikya== NULL || output==NULL ) return MATAMIKYA_NULL_ARGUMENT;
    fprintf(output,"Best Selling Product:\n");
    if(matamikya->warehouse==NULL) {
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }
        ASElement best_selling ;
        double max_selling = 0 ;
        AS_FOREACH(ASElement , element , matamikya->warehouse)
        {
           if( (*(ProductData)element).total_sold > max_selling )
           {
               best_selling=element ;
               max_selling = (*(ProductData)element).total_sold ;
           }
        }
        if(max_selling == 0)
        {
            fprintf(output,"none\n");
            return MATAMIKYA_SUCCESS;
        }
    mtmPrintIncomeLine((*(ProductData)best_selling).Name,(*(ProductData)best_selling).Id,(*(ProductData)best_selling).total_sold, output );
        return MATAMIKYA_SUCCESS;
    }
