// De includes laten we achterwege (triviaal).

// Zo zou ModelSelectControl er uit hebben gezien als het een 
// eigen taak zou hebben gehad:
class ModelSelectControl : public rtos::task<>, 
	public IModelDatabeheerListener, public ITouchAreaListener
{
private:
	rtos::flag flagStart;
	rtos::flag flagFilenames;
	rtos::pool<std::array<string,MAXFILES>> poolFilenames;
	rtos::queue<ITouchArea*> taQueue;
	
	std::array<string,MAXFILES>    arFilenames;
	std::array<TouchArea,MAXFILES> arTaBestanden;
	TouchArea taPijlOmhoog, taPijlOmlaag, taAfbreken;
	
	DisplayControl& displayControl;
	
	enum state_modelSelect_t = {Idle, Laden, GeenFiles, LijstTonen}
	state_modelSelect_t state_modelSelect = state_modelSelect::Idle;
	
public:
	ModelSelectControl(TouchDetector& touchDetector, DisplayControl& displayControl):
		displayControl(displayControl): flagStart(this), flagFilenames(this), poolFilenames(this), taQueue(this))
	{
		// Register this ModelSelectControl object as listener to its 
		// TouchArea objects:
		taPijlOmhoog.addTouchAreaListener(this);
		taPijlOmlaag.addTouchAreaListener(this);
		taAfbreken.addTouchAreaListener(this);
		// The TouchDetector in this case serves as a Handler class
		// for TouchAreas. The TouchAreas need to be registered at it.
	    touchDetector.addTouchDetectorListener(taPijlOmhoog);
		touchDetector.addTouchDetectorListener(taPijlOmlaag);
		touchDetector.addTouchDetectorListener(taAfbreken);
	}
	
    void touched(TouchArea* pTa)
	{
		taQueue.write(pTa);
	}

    void filenamesKlaar(std::array<string,MAXFILES> filenames)
	{
		poolFilenames.set(filenames);
		flagFilenames.set();
	}
	
	void start()
	{
		flagStart.set();
	}
	
	void toonlijst(int indexEersteFile)
	{  
		// ... deze convenience functie is te kopieren uit de STD.
	}
	
	void getLijstEntryIndexVanTouch(TouchArea* pTa)
	{  
		// ... deze convenience functie is te kopieren uit de STD.
	}
	
	void main()
	{
		int indexEersteFile = 0;
		
		for(;;)
		{
			switch (state_modelSelect):
			{
				case state_modelSelect_t::Idle:
					wait(flagStart);
					indexEersteFile = 0;
					state_modelSelect = state_modelSelect_t::Laden;
					break;
					
				case state_modelSelect_t::Laden:
					displayControl.clearScreen();
					toonText(0,0,"Aan het laden...");
					modeldatabeheer.queryFilenames();
					wait(flagFilenames);
					arFilenames = poolFilenames.read();
					
					if(arFilenames.size()>0)
					{
						state_modelSelect = state_modelSelect_t::LijstTonen;
					}
					else
					{
						state_modelSelect = state_modelSelect_t::GeenFiles;
					}
					break;
					
				case state_modelSelect_t::LijstTonen
				{
					displayControl.clearScreen()
					toonLijst(indexEersteFile);
					toonButton(0,SCREENHEIGHT-FONTHEIGHT,"Afbreken");
					toonButton(0,SCREENHEIGHT-2*FONTHEIGHT,"Omlaag");
					toonButton(0,SCREENHEIGHT-3*FONTHEIGHT,"Omhoog");
					
					wait(taQueue);
					pTa = taQueue.read();
					if(pTa==&taAfbreken)
					{
						modeldatabeheer.setup(""); // geen filenaam gekozen
						hoofdMenuControl.start();
						state_modelSelect = state_modelSelect_t::Idle;
					}
					else if (pTa==&taOmlaag)
					{
						if(indexEersteFile<filenames.size()-MAXFILES)
						{
							indexEersteFile++;
						}		
						// terug naar zelfde state: voor de duidelijkheid:
						state_modelSelect = state_modelSelect_t::LijstTonen;						
					}
					else if (pTa==&taOmhoog)
					{
						if(indexEersteFile>0)
						{
							indexEersteFile--;
						}		
						// terug naar zelfde state: voor de duidelijkheid:
						state_modelSelect = state_modelSelect_t::LijstTonen;						
					}
					else
					{
						int lijstIndex = getLijstEntryIndexVanTouch(pTa);
						if(lijstIndex != -1)
						{
							fileIndex=lijstIndex+indexEersteFile;
							if(fileIndex<filenames.size())
							{
								modeldatabeheer.setup(filenames[fileIndex])
								hoofdMenuControl.start();
								state_modelSelect = state_modelSelect_t::Idle;
							}
						}
						// terug naar zelfde state: voor de duidelijkheid:
						state_modelSelect = state_modelSelect_t::LijstTonen;	
					}
				}
				case state_modelSelect_t::GeenFiles:
					displayControl.clearScreen();
					toonText2(0,0,"Geen of lege SD Kaart");
					toonbutton(0,SCREENHEIGHT-FONTHEIGHT,"Afbreken");
					wait(taQueue);
					pTa = taQueue.read();
					if(pTa==&taAfbreken)
					{
						modeldatabeheer.setup(""); // geen filenaam gekozen
						hoofdMenuControl.start();
						state_modelSelect = state_modelSelect_t::Idle;
					}
					break;
					
				default:
					assert(false); // Report error: no valid state.
					break;
			}
		}
	}
}