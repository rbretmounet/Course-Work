hrs = input("Enter Hours:")
h = float(hrs)
rate = input("Enter Hourly Rate:")

if h <= 40:
    print(h*float(rate))
else:
    print(((h-40)*((float(rate))*1.5))+(float(rate)*40))
