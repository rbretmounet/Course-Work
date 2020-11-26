def computepay(h,r):
    if h < 40:
        pay = h*r
    else:
        pay = (40*r)+((h-40)*(1.5*r))

    return pay

hrs = input("Enter Hours:")
rate = input("Enter Rate Per Hour")
p = computepay(float(hrs),float(rate))
print("Pay",p)
