# Rules

 - No consecutive numbers or names or any combination thereof <- implemented in tokenizer
 - No consecutive operators <- implemented in tokenizer
 - No leading operator <- implemented in analyze
 - No number on left side of the = <- implemented in analyze
 - Only 1 = per expression <- implemented in analyze
 - <s>No numbers in names, they will be treated as numbers</s> lifted, var0 is allowed now