# Karnaugh priemtermen en formules

## Criteria 
- De uitgangsvariabele van de formule is wat er linksboven het Karnaugh diagram staat.
- Doorsneden zijn met logische AND (&& of ^) aangegeven.
- Verenigingen zijn met logische OR (|| of v) aangegeven.
- De doorsneden (de priemtermen) worden zijn groot mogelijk gekozen.
- Daarbij is benut dat als je karnaugh-diagrammen "opvouwt", dat dan boven elkaar gelegen velden ook aan elkaar grenzen.
- Afmetingen van priemtermen in een richting zijn altijd een macht van 2.
- Priemtermen met een lengte van pow(2,n) moeten een startpositie hebben op een veelvoud van pow(2,n-1).
  Dus bijvoorbeeld een priemterm van 4 velden (pow(2,2)) breed moet starten op x = 0, 2, 4, 6, .. etc. Dus op veelvouden van 2 velden (pow(2,2-1)).
- De doorsneden zijn eerst toegepast, en daarna pas de verenigingen.  
  Dus bijvoorbeeld: Y = (A ^ B) v (C ^ D).
- Karnaugh diagrammen zijn zo "vierkant" mogelijk gekozen.
  Dus bijvoorbeeld bij 32 velden: 4x8 of 8x4, niet 16x2 of 32x1.