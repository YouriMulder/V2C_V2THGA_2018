# V2C_V2THGA_2018

In deze repository staan alle benodigde bestanden voor onze game.
Er is een specifieke mappenstructuur nodig voor het opstarten van deze game.
Hieronder een korte uitleg wat er nodig is en gedaan moet worden om deze game te spelen.

Allereerst clone de repository naar een door u gekozen map.

De volgende programma's en libraries zijn nodig:

SFML(2.5.1): https://www.sfml-dev.org/download/sfml/2.5.1/ 
	-Download de "visual c++ 15(2017) - 32bit" versie van SFML.<br/>
	-Pak de .zip file uit. <br/> 
	-Maak in de map waar de repository staat een nieuwe map aan met de naam "dependencies". <br/>
	-Plaats de uitgepakte map "SFML-2.5.1" in de dependencies map. <br/> 
	
premake5: https://premake.github.io/download.html#v5
	-Download premake5 vanaf bovenstaande link. <br/>
	-Pak de .zip file uit.<br/>
	-Plaats het premake5.exe bestand in de map waar de repository staat. <br/>
	
Het maken van de .sln file. <br/>
	-Open een commandprompt. <br/>
	-Gebruik cd om naar de directory van de repository te gaan.<br/>
	-Run hier het volgende command "premake5 vs2017".<br/>
	-Er is nu een solution aangemaakt in de build map.<br/>

Vanaf dit punt kan de .sln file in de build map geopend worden met visual studio 2017.

In visual studio kan er op zowel release als debug gecompiled worden.
Let wel op debug is de game soms wat traag dus het beste is om op release te compilen.

LET OP!!!!: Wanneer de .exe is gecompiled en gestart wordt vanuit visual studio is er geen probleem.
			Echter als deze al gecompiled is en de .exe wordt rechtstreeks vanuit de windows file explorer gestart. 
			Deze moet even verplaatst worden vanuit de release/debug map naar de bin map. 


Hieronder een korte beschrijving van de mappenstructuur:
src: In deze map staat alle code (hpp en cpp files). <br/>
build: In deze map staan alle visual studio files (.sln,.vcxproj etc.).<br/>
bin: In deze map komt de uiteindelijke .exe file terecht hier wordt een onderscheid gemaakt tussen release en debug.<br/>
res: In deze map staan alle benodigde textures, levelfiles en sounds.<br/>
dependencies: In deze map staan de libraries(SFML).<br/>
doxygen: In deze map staat de doxyfile om doxygen te genereren. <br/>

Voor de al gegenereerde doxygen kan op de volgende drive link gekeken worden: https://drive.google.com/drive/folders/1mIEU50SaadVVD8oHtJi7dGHnunT0mfuu?usp=sharing 
