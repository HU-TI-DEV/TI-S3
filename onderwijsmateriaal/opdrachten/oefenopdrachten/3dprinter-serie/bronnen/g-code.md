## GCode

G-code is een taal die veelvuldig wordt gebruikt in computerondersteunde productie om geautomatiseerde machinegereedschappen te besturen, inclusief 3D-printers. G-code commando's sturen de machine aan, instruerend waar naartoe te bewegen, hoe snel te bewegen en welk pad te volgen.

Voor 3D-printers wordt G-code gegenereerd door slicer-software, die een 3D-model vertaalt naar een instructieset voor de printer om het object laag voor laag te creëren.

### Voorbeeld

In het onderstaande voorbeeld wordt het gebruik van de belangrijkste G-code commando's gedemonstreerd:

**G90** ; absolute positionering. **G91** zou relatieve positionering selecteren.  
**M82** ; absolute extrusie. **M83** zou relatieve extrusie selecteren.  
**M106 S0** ; ventilator op nul snelheid  
**M140 S85** ; stel bedtemperatuur in  
**M190 S85** ; stel bedtemperatuur in en wacht op het bereiken ervan  
**G28** ; auto-homing, verplaats naar min endstops  
**M400** ; voltooi bewegingen  
**M104 S250** ; stel hotend-temperatuur in  
**M109 S250** ; stel hotend-temperatuur in en wacht op het bereiken ervan.  
**G29** ; bednivellering  
**M400** ; voltooi bewegingen  
**G1 X1 Y1 Z0.3 F1000** ; verplaats naar startpunt op X,Y,Z met snelheid 1000mm/min.  
**M109 S250** ; wacht tot hotend temperatuur bereikt  
**G1 X1.0 E9.0 F1000.0** ; start nozzle reiniging (verplaats naar X1 met extrusiehoeveelheid 9 bij snelheid 1000)  
**G1 X100.0 E12.5 F1000.0** ; voltooi nozzle reiniging  
**G1 X103.505 Y153.291 E4.5648** ; teken iets, beweging en extrusie in XY vlak. De extrusiehoeveelheid is normaal in mm.  
**G1 X103.291 Y153.505 E4.5804** ; beweging en extrusie in XY vlak  
**G1 Z0.600 F3000** ; wijzig laag  
**G1 X104.025 Y154.025 F9000** ; enkel beweging in XY vlak. Eenheden zijn normaal in mm  
**G1 X95.975 Y154.025 E0.4133 F1397** ; beweging en extrusie in XY vlak

Wanneer een G-code commando zoals **G1 F1800 X10 Y10 E5** wordt verzonden, verplaatst de printer het kopstuk vanaf zijn huidige positie naar de positie **(X10, Y10)** terwijl er **5mm** filament wordt geëxtrudeerd.  
De beweging en extrusie beginnen en eindigen tegelijkertijd, en de snelheid van de beweging wordt bepaald door de doorvoersnelheid (**F1800** in dit geval, wat meestal staat voor **1800mm/minuut**).

Hierboven, als **E5** zou ontbreken, zou het resultaat hetzelfde zijn, maar dan zonder enige extrusie.