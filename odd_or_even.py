
try :
    number=int(input("enter a number"))
    if(number%2 == 0 or number ==0):
        print(number," is an even number")
    else:
        print(number," is an odd number")
except:
    print("enter a valid number")
    