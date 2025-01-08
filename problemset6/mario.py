def get_user_input():
    while True:
        input_user = input("Height: ")
        if not input_user.isdigit():
            continue
        input_user = int(input_user)
        if input_user >= 1 and input_user <= 8:
            return input_user

def print_blocks():
    number_blocks = get_user_input()
    for number in range(1, number_blocks+1):
        print(f"{' '*(number_blocks - number)}{'#'*number}  {'#'*number}")

if __name__ == '__main__':
    print_blocks()