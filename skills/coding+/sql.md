
#If Exists Update Else Insert

```sql
UPDATE Table1 SET (…) WHERE Column1=’SomeValue’

IF @@ROWCOUNT=0

    INSERT INTO Table1 VALUES (…)
```
