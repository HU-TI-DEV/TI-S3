// Millis value when the data was last sent. 
long timeLastSent;

// Interval (milliseconds) between sending analog data
const unsigned SendInterval = 5; // [ms]

const int FIR_size = 11;  // must be an odd number (to keep finding the median simple)
int arMeasurements[FIR_size];
int arTmp[FIR_size];
int nLastMeasurementIndex=0;

void setup() {
  Serial.begin(115200);

  timeLastSent = millis();
}

int getMedian()
{
	// TODO: implementeer zelf
  return 0;
}

int getAverage()
{
  return 0; // TODO: implementeer zelf
}

// Tip: Je kunt de serieel geprinte nummers ook via Serial Monitor (in plaats van Serial Plotter) weergeven.
// Google daarvoor evt op Serial Plotter - Arduino IDE.
void loop() {
  if ((millis() - timeLastSent) > SendInterval)
  {
    timeLastSent = millis();
    int dataValue = analogRead(0);
    nLastMeasurementIndex = (nLastMeasurementIndex+1)%FIR_size;
    arMeasurements[nLastMeasurementIndex]=dataValue;
     //Serial.print(dataValue);
    //Serial.print(" ");
    //Serial.print(getMedian());
    //Serial.print(" ");
    Serial.println(getAverage());
  }
}
