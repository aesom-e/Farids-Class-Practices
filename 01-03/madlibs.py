name_of_a_farm = input("Name of a farm: ")
name = input("Name: ")
# Use .lower to ensure that the user doesn't input using capital letters where it wouldn't fit in
silly_adjective = input("Silly adjective: ").lower()
emotion = input("Emotion: ").lower()
farm_tool = input("Farm tool: ").lower()
funny_action = input("Funny action ending in \"-ing\": ").lower()
farm_equipment = input("Piece of farm equipment: ").lower()
large_animal = input("Large animal: ").lower()
object_name = input("Object: ").lower()
dramatic_action = input("Dramatic action in past tense: ").lower()
place_in_nature = input("Place in nature: ").lower()
exclamation = input("What an escapee would yell: ")
adjective = input("Adjective to describe an adventure: ").lower()

madlib = f"One morning at {name_of_a_farm}, a clever chicken named {name} decided it was time to break out of the coop. " + \
         f"With their {silly_adjective} feathers fluffed up and their {emotion} beak set in determination, they devised a plan. " + \
         f"First, they used a {farm_tool} to dig a tunnel under the fence. Then, they distracted the farmer by {funny_action} near the {farm_equipment}. " + \
         f"Just as they were about to make a run for it, a {large_animal} blocked the path! Thinking fast, {name} grabbed a {object_name} and {dramatic_action} over the obstacle. " + \
         f"At last, freedom! They ran towards the {place_in_nature}, flapping their wings and shouting, \"{exclamation}!\" It was the most {adjective} day of their life."

print(f"\n{madlib}")