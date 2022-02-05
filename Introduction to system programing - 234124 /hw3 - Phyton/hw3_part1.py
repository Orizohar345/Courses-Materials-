import string


def try_to_add(name, price, amount, matamikya):
    if name in matamikya or price < 0 or amount < 0 :
        return
    else:
        matamikya[name] = {"price": price, "amount": amount, "profit": 0}


def try_to_change_amount(name, new_amount, matamikya):
    if name not in matamikya:
        return
    matamikya[name]["amount"] += new_amount


def try_to_ship_order(products_list, matamikya):
    list_range = range(len(products_list))
    for e in list_range[::2]:
        if products_list[e] in matamikya:
            if matamikya[products_list[e]]["amount"] > 0 and float(products_list[e+1]) > 0 and\
                    matamikya[products_list[e]]["amount"]-round(float(products_list[e+1]), 4) >= 0:
                matamikya[products_list[e]]["amount"] -= round(float(products_list[e+1]), 4)
                matamikya[products_list[e]]["profit"] += round(matamikya[products_list[e]]["price"]*float(products_list[e+1]), 4)


def update_warehouse(filename):
    add_command = "add product".split()
    change_amount_command = "change amount".split()
    ship_order_command = "ship order".split()
    file = open(filename , 'r')
    matamikya = {}
    for l in file:
        line = l.split()
        if line[0:2] == add_command :
            try_to_add(line[2], round(float(line[3]), 4), round(float(line[4]), 4), matamikya)
        elif line[0:2] == change_amount_command :
            try_to_change_amount (line[2], round(float(line[3]), 4),matamikya)
        elif line[0:2] == ship_order_command :
            seperated_line = l.replace(",", "")
            seperated_line = seperated_line.replace("--", "")
            try_to_ship_order(seperated_line.split()[2::], matamikya)
    file.close()
    return matamikya


def find_best_selling_product(file_name):
    matamikya = update_warehouse(file_name)
    sorted_products_name = sorted(matamikya)
    size = range(len(sorted_products_name))
    max = {"name": "", "current_selling_price": 0}
    for e in size:
        if matamikya[sorted_products_name[e]]["profit"] > max["current_selling_price"]:
            max["name"] = sorted_products_name[e]
            max["current_selling_price"] = matamikya[sorted_products_name[e]]["profit"]
    best_selling_product = (max["name"], max["current_selling_price"])
    return best_selling_product


def find_k_most_expensive_products(file_name, k):
    matamikya = update_warehouse(file_name)
    matamikya_size = len(matamikya)
    most_k_expensive_products = []
    if k <= 0 or matamikya_size == 0:
        return most_k_expensive_products
    fixed_k = k
    if k > matamikya_size:
        fixed_k = matamikya_size
    sorted_products_name = sorted(matamikya)
    for i in range(fixed_k):
        sorted_products_name_size = len(sorted_products_name)
        current_expensive_product = {"name": "", "price": -1}
        for j in range(sorted_products_name_size):
            if matamikya[sorted_products_name[j]]["price"] > current_expensive_product["price"]:
                current_expensive_product["name"] = sorted_products_name[j]
                current_expensive_product["price"] = matamikya[sorted_products_name[j]]["price"]
        sorted_products_name.remove(current_expensive_product["name"])
        most_k_expensive_products.append(current_expensive_product["name"])
    return most_k_expensive_products

















