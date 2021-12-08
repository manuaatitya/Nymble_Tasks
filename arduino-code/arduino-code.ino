String dataToTransmit = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum";
String dataReceived = "";

bool dataTransmissionComplete = false;   // Flag to indicate Data tranmission is over
int counter = 0;

float dataTransferRate = 0;   // Variable to find the data Transmission rate

# define BAUD_RATE 2400   // Define the baud rate to be used for the serial communication

void setup()
{
  Serial.begin(BAUD_RATE);
}

void loop()
{
  // If data is still there to be sent
  if (dataTransmissionComplete == false) sendData(counter, dataTransmissionComplete);

  // Check if some data is received on Serial Port
  receiveData(counter);
  
  counter ++;
}

void sendData(int counter, bool dataTransmissionComplete)
{
  if(dataTransmissionComplete == false)
  {
    if((20 * counter + 20) > dataToTransmit.length())
    {
      Serial.print(dataToTransmit.substring(20 * counter));
      dataTransmissionComplete = true;
    }
    else Serial.print(dataToTransmit.substring(20*counter, 20*counter + 20));
  }
}

void receiveData(int counter)
{
  String input_data;
  unsigned long start_time = millis();
  while(Serial.available() > 0)
  {
    input_data = Serial.readString();
    dataReceived += input_data;
  }
  unsigned long end_time = millis();
  unsigned long time_elapsed = (end_time - start_time);
  dataTransferRate = (dataTransferRate + (float)(sizeof(input_data))/(time_elapsed))/counter;
}
