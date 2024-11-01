// De includes laten we achterwege (triviaal).

// Zo ziet ModelSelectControl er uit zonder eigen taak.
class ModelSelectControl : 
    public IModelDatabeheerListener, public ITouchAreaListener
{
private:
    // De taak (waarom ModelSelectControl control is samengevoegd)
	rtos::task<>* pTask;
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
    // Initialise the synchronisation elements on the task, which
	// is passed, in this case:
	ModelSelectControl(rtos::task<>* pTask,
		TouchDetector& touchDetector, DisplayControl& displayControl):
		pTask(pTask),flagFilenames(pTask), poolFilenames(pTask),
		taQueue(pTask), displayControl(displayControl)
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
		
	void toonlijst(int indexEersteFile)
	{  
		// ... deze convenience functie is te kopieren uit de STD.
	}
	
	void getLijstEntryIndexVanTouch(TouchArea* pTa)
	{  
		// ... deze convenience functie is te kopieren uit de STD.
	}
	
	void start()
	{
		int indexEersteFile = 0;
		state_modelSelect = state_modelSelect_t::Laden;
		bool bStopNu = false;
		for(;;)
		{
			switch (state_modelSelect):
			{
				case state_modelSelect_t::Laden:
					displayControl.clearScreen();
					toonText(0,0,"Aan het laden...");
					modeldatabeheer.queryFilenames();
					pTask->wait(flagFilenames);
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
					
					pTask->wait(taQueue);
					pTa = taQueue.read();
					if(pTa==&taAfbreken)
					{
						modeldatabeheer.setup(""); // geen filenaam gekozen
						bStopNu = true;
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
								bStopNu = true;
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
					pTask->wait(taQueue);
					pTa = taQueue.read();
					if(pTa==&taAfbreken)
					{
						modeldatabeheer.setup(""); // geen filenaam gekozen
						bStopNu = true;
					}
					break;
				default:
					assert(false); // Report error: no valid state.
					break;
			}
			if(bStopNu)
			{
				break;
			}
		}
	}
}