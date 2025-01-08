def check_number_start(credit_card):
    lenght_credit_card = len(credit_card)
    if credit_card.startswith(("34", "37")) and lenght_credit_card == 15:
        return True, "AMEX"
    elif credit_card.startswith(("51", "52", "53", "54", "55")) and lenght_credit_card == 16:
        return True, "MASTERCARD"
    elif credit_card.startswith("4") and lenght_credit_card in (13, 16):
        return True, "VISA"
    return False, ""

def validate_sum(credit_card):
    sum_digits = 0
    for index, number in enumerate(reversed(credit_card)):
        digit = int(number)
        if index % 2 == 1:
            digit = digit * 2
            sum_digits += digit if digit < 10 else digit - 9
        else:
            sum_digits += digit
    return sum_digits % 10 == 0

def print_invalid():
    print("INVALID")

def validate_credit_card():
    credit_card = input("Number: ")
    is_valid, flag = check_number_start(credit_card)
    if not is_valid:
        return print_invalid()
    if not validate_sum(credit_card):
        return print_invalid()
    print(flag)

if __name__ == '__main__':
    validate_credit_card()
