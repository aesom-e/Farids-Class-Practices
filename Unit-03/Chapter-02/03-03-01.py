import os

def fill_line(item: str, price: float) -> str:
    line_len = len("--------------------------\n")
    item_line = f"{item}{price:.2f}\n"
    return item_line[:len(item)] + " " * (line_len - len(item_line)) + item_line[len(item):]

receipt = os.path.join(os.path.dirname(__file__), 'receipt.txt')
with open(receipt, 'w') as f:
    # Write the recipt's header
    f.write("--- Welcome to Wendy's ---\n"
            "Wendy's Store # 12345\n"
            "Server: Chicken\n"
            "--------------------------\n"
            "ITEM                 PRICE\n")
    
    # Handle user input
    total = 0
    while name := input("Item: "):
        cost = float(input("Cost: "))
        total += cost

        # Write it to the file
        f.write(fill_line(name, cost))
    
    # Write the footer
    f.write("--------------------------\n")
    f.write(fill_line("Subtotal", total))
    f.write(fill_line("Taxes", total*0.13))
    f.write(fill_line("Total", total*1.13))
    f.write("Thank you for shopping at\n"
            "Wendy's, enjoy.")