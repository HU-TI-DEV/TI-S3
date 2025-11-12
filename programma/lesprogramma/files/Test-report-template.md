# Doel
Beschrijf hier het doel van je test.

# Succes criteria
Beschrijf hier wanneer je test geslaagd is. Dit is vaak mooi in een tabel:

| # | Test Aspect | Success Criterion   | Pass/Fail Threshold |
|---|---|---|---|
| 1 | Latency | Average response time < **10 ms** |   Pass if < 10 ms     |
| 2 | Throughput              | System can handle ≥ **1000 requests/s**      | Pass if ≥ 1000/s    |
| 3 | Accuracy                | Output error < **0.5%** | Pass if < 0.5%      |
|10 | User Experience (UX)    | ≥ **90%** of users report satisfaction | Pass if ≥ 90%       |

# Test setup
Beschrijving van alle spullen die je nodig hebt voor de test, maar ook bv test condities (het mag niet warmer zijn dan 30 graden, etc). 
bv:
- FLuke multimeter model 287
- ESP CYD

Vaak helpt het ook om een schema of foto van de testopstelling te hebben. 

# Stappenplan / test scenario
Beschrijf in een stappen plan wat de tester moet doen. 
Bv:
1) Sluit de ESP aan op de USB aansluiting van je laptop.
2) Start een terminal (liefst real term, maar een andere terminal kan ook).
3) Start de logging to file van de terminal (zie bla bla )
4) etc.. bla bla 

# Meetresultaten (& discussie)
De resultaten. Liefst in grafieken of tabellen als het kan. Je kan er ook een stuk discussie aan toevoegen. 

# Conclusies
Conclusies moeten volgen uit de test data en mogen niet uit de lucht komen vallen. Vaak is een tabel weer fijn. 

| # | Test Aspect | Success Criterion   | Value|
|---|---|---|---|
| 1 | Latency | Average response time < **10 ms** |  4 ms with a stdev of 1 ms  |
| 2 | Throughput              | System can handle ≥ **1000 requests/s**      | 3000 request is limit    |
