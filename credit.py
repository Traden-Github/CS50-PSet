def main():
    card = input("Number: ")
    result = validate(card)
    print(result)


def validate(card):
    if luhn(card) == True:
        return cardtype(card)
    else:
        return "INVALID"


def luhn(card):
    productSum = 0
    Sum = 0
    for i in range(len(card)):
        j = len(card) - i - 1
        if (i + 1) % 2 == 0 and int(card[j]) < 5:
            productSum += int(card[j]) * 2
        elif (i + 1) % 2 == 0:
            first = int(card[j]) * 2 // 10
            second = int(card[j]) * 2 % 10
            productSum += first + second
        else:
            Sum += int(card[j])
    total = productSum + Sum
    if total % 10 == 0:
        return True
    else:
        return False


def cardtype(card):
    if card[0:1] == "4" and (len(card) == 13 or len(card) == 16):
        return "VISA"

    d2 = card[0:2]
    if (d2 == "34" or d2 == "37") and len(card) == 15:
        return "AMEX"

    match int(d2):
        case 51 | 52 | 53 | 54 | 55:
            if len(card) == 16:
                return "MASTERCARD"
    return "INVALID"


if __name__ == "__main__":
    main()
