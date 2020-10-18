# Code for RSA Encryption and Decryption
def RSA():
    p = int(input("Enter prime value for p: "))
    q = int(input("Enter prime value for q: "))

    # Calculate the public key
    n = p * q
    print("Public key is: " + str(n))
    e = int(input("Enter a small exponent and greater then 1: "))

    h = (p - 1)*(q - 1)

    # Can be any constant value
    k = 2

    # Calculating the private key
    pri = int((k * h + 1) / e)
    print("Private key is: " + str(pri))

    T = ""
    text = input("Enter Letters to encrypt: ")

    # Changing the entered letters into ints
    # Combing the ints and changing them into a string
    # Ex: Entered: HI -> H = 8 and I = 9 then string = 89
    for i in text:
        number = ord(i) - 64
        T += str(number)
        print(i + " value is: " + T)

    # Changing the string of the combined ints into a int
    T = int(T)

    # Encrypting the letters based on the public key
    encr = (T**e) % n
    print(encr)

    # Decrypting the letters based on the private key
    Decr = (encr**pri) % n
    print("The decrypted value is: " + str(Decr) + " which is " + text)
RSA()
