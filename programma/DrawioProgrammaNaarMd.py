import os
import xml.etree.ElementTree as ET

# Inputs:
# intro.md          (header text van de pagina)
# Programma.drawio  (programma tabel)

# Output:
# README.md

# Gebruiksaanwijzing:
# 1. Update Programma.drawio met de desktop versie van drawio.
# 2. Klik op het batchbestand dat onderstaande script uitvoert.
# 3. Export vanuit het gegenereerde Programma_for_export_html.drawio een html
#
# Binnen een seconde is README.md gesynct met de content in Programma.drawio
# en intro.md

def read_drawio_file_into_tree(filename):
    # Parse the XML content into an ElementTree
    tree = ET.parse(filename)
    root = tree.getroot()
    return tree,root

# Voorbeeld: een blok in de swimlane met de naam "Onderwijsvrij" met een
# hoogte van 80, terwijl itemheight=20, beslaat 4 tijds-items/delen.
# Het resulteert in het 4 x toevoegen van de string "Onderwijsvrij"
# aan de output list (een keer voor elke dag)
def SwimlaneSplitupToList(root, swimlane_name, splitupHeight):
    sprint_list = []
    for diagram in root.findall('.//diagram'):
        mxGraphModel = diagram.find('mxGraphModel')
        root_element = mxGraphModel.find('root')
        # Zoek de swimlane met de opgegeven naam
        for object in root_element.findall('object'):
            if object.get('label') == swimlane_name and 'swimlane' in object.find('mxCell').get('style', ''):
                # Deze object is de gezochte swimlane
                swimlane_id = object.get('id')
                # Verzamel alle child-objecten van deze swimlane
                for child in root_element.findall('mxCell'):
                    if child.get('parent') == swimlane_id:
                        label = child.get('value')
                        mxGeometry = child.find('mxGeometry')
                        height = int(mxGeometry.get('height'))
                        count = height // splitupHeight
                        sprint_list.extend([label] * count)
    return sprint_list

# Voorbeeld: een blok in de swimlane met de naam "Sprint 1" met een
# hoogte van 80, terwijl itemheight=20, beslaat 4 tijds-items/delen.
# De bijbehorende output-tuple in de list wordt dus:
# (4,"Sprint 1")
def SwimlaneExtractItemTuples(root, swimlane_name, itemHeight):
    sprint_list = []
    for diagram in root.findall('.//diagram'):
        mxGraphModel = diagram.find('mxGraphModel')
        root_element = mxGraphModel.find('root')
        # Zoek de swimlane met de opgegeven naam
        for object in root_element.findall('object'):
            if object.get('label') == swimlane_name and 'swimlane' in object.find('mxCell').get('style', ''):
                # Deze object is de gezochte swimlane
                swimlane_id = object.get('id')
                # Verzamel alle child-objecten van deze swimlane
                for child in root_element.findall('mxCell'):
                    if child.get('parent') == swimlane_id:
                        label = child.get('value')
                        mxGeometry = child.find('mxGeometry')
                        height = int(mxGeometry.get('height'))
                        count = height // itemHeight
                        sprint_list.append((count,label))
    return sprint_list

# CollapsableItems start with spaces to make room for the foldout (+) symbol.
# Die moeten dus verwijderd worden.
def VerwijderLeadingSpaties(lst):
    lstOut=list()
    for tuple in lst:
        str = tuple[1]
        while str.startswith("&nbsp;"):
            str = str.replace("&nbsp;", "", 1).lstrip()
        lstOut.append((tuple[0],str))
    return lstOut

# CollapsableItems start with spaces to make room for the foldout (+) symbol.
def SwimLaneExtractCollapsableItemTuples(root, swimlane_name, itemHeight):
    lstComposedItemTuples = SwimlaneExtractItemTuples(root, swimlane_name, itemHeight)
    lstComposedItemTuples = VerwijderLeadingSpaties(lstComposedItemTuples)
    return lstComposedItemTuples

# Voeg de kolommen met informatie samen tot een .md document.
def generate_markdown(intro, sprints, projects, weeks, sessions):
    md_content = []
    md_content.append(intro)
    md_content.append("## Programma")
    md_content.append("[(alternatieve view html)](https://hu-ti-dev.github.io/TI-S3/programma/Programma_for_export_html.drawio.html)")
    md_content.append("")

    while sprints:
        # Verwerk de sprint
        sprint_days, sprint_name = sprints.pop(0)
        md_content.append(f"### {sprint_name}\n")
        
        # Verwerk het project
        if projects:
            project_days, project_text = projects.pop(0)
            md_content.append(f"{project_text}\n")

        total_week_days = 0
        while total_week_days < sprint_days:
            # Verwerk de week
            if weeks:
                week_days, week_name = weeks.pop(0)

                # In .md willen we de week namen zonder carriage returns:
                week_name = week_name.replace('<br>',' ')
                week_name = week_name.replace('<br style="border-color: var(--border-color);">',' ')
                
                md_content.append(f"\n#### {week_name}\n")
                total_week_days += week_days
            
                # Maak een tabel met sessies
                md_content.append("| **Dag** | **Kennissessie** |")
                md_content.append("|---|---|")
                days = ["ma", "di", "wo", "do"]
                
                for day in days:
                    session_text = sessions.pop(0) if sessions else "Geen sessie gepland"
                    md_content.append(f"| {day} | {session_text} |")
        
        # Een extra newline voor leesbaarheid tussen sprints
        md_content.append("\n")
    
    md_content.append("#### Docenten-info:\n")
    md_content.append("Deze pagina is gegenereerd uit: [./Programma.drawio](./Programma.drawio) met het volgende script: [./DrawioProgrammaNaarMd.py](./DrawioProgrammaNaarMd.py)\n")
    md_content.append("De alternatieve view is uit diezelfde drawio gegenereerd via export naar HTML (uncheck lightbox en uncheck zoom to fit)\n")

    return "\n".join(md_content)

def read_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    return content

def write_file(content, filename):
    with open(filename, 'w', encoding='utf-8') as file:
        file.write(content)

# Get the directory of the current script
script_dir = os.path.dirname(os.path.abspath(__file__))
input_fullpath = os.path.join(script_dir, "Programma.drawio")
intro_fullpath = os.path.join(script_dir, "intro.md")

tree, root = read_drawio_file_into_tree(input_fullpath)

# Extraheer de data uit de swimlanes en print voor debugging/verificatie.
print("kennissessie_list")
kennissessie_list = SwimlaneSplitupToList(root,"Kennissessies",splitupHeight=20)
print(kennissessie_list)

sprint_list = SwimlaneExtractItemTuples(root,"Sprint",itemHeight=20)
print(sprint_list)

print("week_list")
week_list = SwimlaneExtractItemTuples(root,"Week",itemHeight=20)
print(week_list)

print("project_list")
project_list = SwimLaneExtractCollapsableItemTuples(root,"Project, MVP",itemHeight=20)
print(project_list)

# Presenteer de data samen in README.md
intro = read_file(intro_fullpath)
markdown = generate_markdown(intro, sprint_list, project_list, week_list, kennissessie_list)
print(markdown)

output_fullpath = os.path.join(script_dir, "README.md")
write_file(markdown,output_fullpath)

# Vanuit de html in github pages linken we terug naar non-github pages... wat vermoedelijk vaker wordt gebruikt.
drawio_for_export_html_fullpath = os.path.join(script_dir, "Programma_for_export_html.drawio")
drawioContent = read_file(input_fullpath)
drawioContent = drawioContent.replace('&lt;a href=&quot;./','&lt;a href=&quot;https://github.com/HU-TI-DEV/TI-S3/tree/main/programma/')
drawioContent = drawioContent.replace('.md&quot;&gt;','.md&quot; target=&quot;_self&quot;&gt;')

write_file(drawioContent,drawio_for_export_html_fullpath)

print("****************************************")
print(" !!! LET OP !!! Vergeet AUB niet vanuit de file Programma_for_export_html.drawio naar html te exporteren voor github pages (disable lightbox).")
print("****************************************")