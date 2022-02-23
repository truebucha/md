
# leaf protocol in reader

<https://leafidentity.com>

<https://www.usmartcards.com/solutions/leaf-cards/>

# lenel on guard

<https://www.lenels2.com/en/us/security-products/onguard/>

# Beacon 

c95c6057-ace2-4598-8b79-c82e219f1a44.54.15716

# QA

## Konstantinb Panel Adaptel - Lenel OnGuard

Identity Server Hostname: cloud.coh-qa.xyz
OAuth Client ID: gdeqlnWKBvcZFo6jxYiJIeqiqaCG5M4UOfdk
OAuth Client Secret: zW8QKR47fdkvF03XjcvcnW8SEdEVdsZO6pZScORfJGASn6R0ib51YDlpHTaNPdyw

# STAGE

## IDS set up
----
## Konstantinb Fake Lenel Panel Adapter

1 Setup device:
```
Identity Server Hostname: cloud.coh-test.xyz
OAuth Client ID: JsTXlaIYftatLJTR7zEn4I5SXvjWcBXlhJ8n
OAuth Client Secret: u5T7X6kW93dzz6OkS1cHOOwlnF4ByB87lnNksfY5JrENAlHLurnkxzj79W1hr5T8
```

2 setup lenel on guard adapter 

3 IDS will add a reader and maintained by itsel (with the name that fake lenel panle will provide)

---

## Konstantinb Pac Panel Adapter

1 setup Self managed Pac adapter

2 setup virtual badge for that adapter

3 Add reader manually using file below

`truu_reader_template-SelfManagedPack.csv`
```
readerId,readerName,buildingId,beaconId,accessLevels,masterKey,credentialKey,readerType
022300000000690F,Konstantinb Leaf Reader,85,022300000000690F,General,00000000000000000000000000000000,00000000000000000000000000000000,LEAF
```

