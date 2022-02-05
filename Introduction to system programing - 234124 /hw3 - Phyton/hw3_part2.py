from operator import itemgetter
from copy import deepcopy


# A function that returns rather or not the given string is a palindrome.
def isPalindrome(string_to_check):
    return string_to_check == string_to_check[::-1]


def get_palindrom_dict(string_to_check):
    # Creating an empty dict and only fitting palindromes will be inserted in it.
    # So if no palindromes are found we'll return an empty dict as requested.
    palindrom_dict = {}
    for k in range(1, len(string_to_check) + 1):  # For each possible palindrome length (
        k_palindroms_to_add = []
        for j in range(len(string_to_check) - k + 1):
            if isPalindrome(string_to_check[j:j+k]):
                k_palindroms_to_add.append(string_to_check[j:j+k])
        if len(k_palindroms_to_add) > 0:
            palindrom_dict[k] = k_palindroms_to_add
    return palindrom_dict


def canTheySwitch(string1, string2):
    string3 = string1
    string4 = ""
    if not len(string1) == len(string2):
        return False
    for i in range(len(string1)):
        if string1[i] == string3[i]:
            string1 = string1.replace(string1[i], string2[i])
        string4 = string4 + string1[i]
    if string4 == string2:
        return True
    return False


# breaking the given string to 2 strings that are consisted of odd indexes and even indexes
# (while index starting from 1)
# returning a bool of rather or not the two strings can 'switch' (as defined in the exercise)
def check_match(string_to_check):
    odd_str = string_to_check[::2]
    even_str = string_to_check[1::2]
    return canTheySwitch(odd_str, even_str)



