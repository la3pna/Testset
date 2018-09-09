#include <scpiparser.h>
#include <Arduino.h>

/*
 * Controller for RF Transceiver Testset
 * 
 * 
 * 
 * Lines are always terminated with /n
*/

#define debug

String idString = "LA3PNA,RF transceiver testset,1,0.1A";

struct scpi_parser_context ctx;
#define RXTXpin 52      // Pin to relay RX/TX
#define anotherpin 53   // don't know yet...
#define localpin 11     // This goes to the local button, GND for local
#define localled 12     // This goes to the local LED
#define clk  8          // clock bus to all of the SPI
#define data 9          // data bus to all of the SPI

 int counter = 0;
 bool remote = LOW;
 int aftxdata = 2;
 int afrxdata = 2;
 int rfrxdata = 2;
 int cpldata = 2;
 int cplold = 1;
 int aftxold = 1;
 int afrxold = 1;
 int rfrxold = 1;
 
void setup() {
  // put your setup code here, to run once:
  scpi_init(&ctx);
  SerialUSB.begin(9600);
  Serial3.begin(9600);
  Serial.begin(9600);
  setup_scpi();
  setup_inputs();
  pinMode(RXTXpin,OUTPUT); digitalWrite(RXTXpin,LOW); // Relaypin low
  pinMode(anotherpin,OUTPUT); digitalWrite(anotherpin,LOW); // anotherpin low
  
  pinMode(localled,OUTPUT); digitalWrite(localled,LOW); // anotherpin low

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);

  delay(100);
  
}

  char line_buffer[256];
  unsigned char read_length;
  int serialport = 0; // 1 = USB, 2 = Serial1, 3 = Serial3;
  
void loop() {
  // put your main code here, to run repeatedly:
 if (SerialUSB.available() > 0)   // see if incoming serial data: 
  { 
    read_length = SerialUSB.readBytesUntil('\n', line_buffer, 256);
    serialport = 1; // 1 for USB
    remote = HIGH;
    digitalWrite(localled,HIGH);  
 
  }
      if (Serial.available() > 0)   // see if incoming serial data:
  { 
    read_length = Serial.readBytesUntil('\n', line_buffer, 256);
    serialport = 2; // 2 for wlan
    remote = HIGH;

    digitalWrite(localled,HIGH);  
  }
        if (Serial3.available() > 0)   // see if incoming serial data:
  { 
    read_length = Serial3.readBytesUntil('\n', line_buffer, 256);
    serialport = 3; // 3 for gpib
    remote = HIGH;

    digitalWrite(localled,HIGH);  
  }
    
   /*
   Lets do all the reading of the pushbuttons.
   */
   if(!remote){
    if(digitalRead(40) && digitalRead(41) && (counter != 100)){counter = 100; String str = ":ROUT:2TONE"; read_length = 11;str.toCharArray(line_buffer, 256);}
    else {
     if((digitalRead(22)==LOW)&&(counter != 1)){counter =  1; String str = ":ROUT:CPL 1";read_length = 11;str.toCharArray(line_buffer, 256);}
     if((digitalRead(23)==LOW)&&(counter != 2)){counter =  2; String str = ":ROUT:CPL 2";read_length = 11;str.toCharArray(line_buffer, 256);}  
     if((digitalRead(24)==LOW)&&(counter != 3)){counter =  3; String str = ":ROUT:CPL 3";read_length = 11;str.toCharArray(line_buffer, 256);}
     if((digitalRead(25)==LOW)&&(counter != 4)){counter =  4; String str = ":ROUT:CPL 4";read_length = 11;str.toCharArray(line_buffer, 256);}
     if((digitalRead(26)==LOW)&&(counter != 5)){counter =  5; String str = ":ROUT:CPL 5";read_length = 11;str.toCharArray(line_buffer, 256);}
     if((digitalRead(27)==LOW)&&(counter != 6)){counter =  6; String str = ":ROUT:CPL 6";read_length = 11;str.toCharArray(line_buffer, 256);}
     if((digitalRead(28)==LOW)&&(counter != 7)){counter =  7; String str = ":ROUT:RFRX 1"; read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(29)==LOW)&&(counter != 8)){counter =  8; String str = ":ROUT:RFRX 2"; read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(30)==LOW)&&(counter != 9)){counter =  9; String str = ":ROUT:RFRX 3"; read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(31)==LOW)&&(counter !=10)){counter = 10; String str = ":ROUT:RFRX 4"; read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(32)==LOW)&&(counter !=11)){counter = 11; String str = ":ROUT:RFRX 5"; read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(33)==LOW)&&(counter !=12)){counter = 12; String str = ":ROUT:RFRX 6"; read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(34)==LOW)&&(counter !=13)){counter = 13; String str = ":ROUT:AFRX 1";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(35)==LOW)&&(counter !=14)){counter = 14; String str = ":ROUT:AFRX 2";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(36)==LOW)&&(counter !=15)){counter = 15; String str = ":ROUT:AFRX 3";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(37)==LOW)&&(counter !=16)){counter = 16; String str = ":ROUT:AFRX 4";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(38)==LOW)&&(counter !=17)){counter = 17; String str = ":ROUT:AFRX 5";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(39)==LOW)&&(counter !=18)){counter = 18; String str = ":ROUT:AFRX 6";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(40)==LOW)&&(counter !=19)){counter = 19; String str = ":ROUT:AFTX 1";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(41)==LOW)&&(counter !=20)){counter = 20; String str = ":ROUT:AFTX 2";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(42)==LOW)&&(counter !=21)){counter = 21; String str = ":ROUT:AFTX 3";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(43)==LOW)&&(counter !=22)){counter = 22; String str = ":ROUT:AFTX 4";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(44)==LOW)&&(counter !=23)){counter = 23; String str = ":ROUT:AFTX 5";read_length = 12;str.toCharArray(line_buffer, 256);}
     if((digitalRead(45)==LOW)&&(counter !=24)){counter = 24; String str = ":ROUT:AFTX 6";read_length = 12;str.toCharArray(line_buffer, 256);}
    }
     }
     if((digitalRead(localpin)==LOW)&&(counter !=25)){counter = 25; String str = "*LOC";read_length = 4;str.toCharArray(line_buffer, 256);Serial.println("LOCAL");}
     if (remote == HIGH){digitalWrite(localled,HIGH);} else {digitalWrite(localled,LOW);} 
    
     if(read_length > 0)
     {
       
        scpi_execute_command(&ctx, line_buffer, read_length);
        read_length = NULL;
        
     }

    // Some logic to avoid the latchup in the SCPI processing
     if(cpldata != cplold){
        spiout(7,cpldata);
        cplold = cpldata;}

     if(rfrxdata != rfrxold){
        spiout(6,rfrxdata);
        rfrxold = rfrxdata;}

     if(aftxdata != aftxold){
        spiout(4,aftxdata);
        aftxold = aftxdata;}

     if(afrxdata != afrxold){
        spiout(5,afrxdata);
        afrxold = afrxdata;}
     }

void spiout(int latchPin,int number){
     digitalWrite(latchPin, LOW);
     uint8_t i;

     for (i = 0; i < 8; i++)  {
        digitalWrite(data, !!(number & (1 << i)));
        digitalWrite(clk, HIGH);
        digitalWrite(clk, LOW);   
        delay(10);         
     }
   
     //take the latch pin high so the LEDs will light up:
     digitalWrite(latchPin, HIGH);
     // digitalWrite(latchPin, LOW);

  }


/*
 * Respond to *IDN?
 */
  scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
if(serialport == 1){
  SerialUSB.println(idString);
  }else if (serialport == 2){
  Serial.println(idString);
  }else if (serialport == 3){
  Serial3.println(idString);
  }else{
      }
   serialport = 0; 
  return SCPI_SUCCESS;
}

scpi_error_t local(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);

  remote = LOW;
  digitalWrite(localled,LOW);
  
  return SCPI_SUCCESS;
}

scpi_error_t rem(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);

  remote = HIGH;
  digitalWrite(localled,HIGH);
  
  return SCPI_SUCCESS;
}


scpi_error_t setRX(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  digitalWrite(RXTXpin,HIGH);
  Serial.println("setRX");
  return SCPI_SUCCESS;
}

scpi_error_t setTX(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
digitalWrite(RXTXpin,LOW);
  Serial.println("setTX");
  return SCPI_SUCCESS;
}

scpi_error_t AFRX(struct scpi_parser_context* context, struct scpi_token* command)
{

  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  unsigned char output_value;

  args = command;
  while(args != NULL && args->type == 0)
  {
    args = args->next;
  }

  output_numeric = scpi_parse_numeric(args->value, args->length, 1e3, 0, 25e6);
  if(output_numeric.length == 0 )
  {
    
   int sel  = (unsigned long)constrain(output_numeric.value, 0, 7);
   sel =pow(2,sel);
   afrxdata = sel;
      #ifdef debug
   Serial.print("afrx selected no: ");
    Serial.println(sel);
 
  #endif
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;
    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }

  scpi_free_tokens(command);

  return SCPI_SUCCESS;
}

scpi_error_t tx2tone(struct scpi_parser_context* context, struct scpi_token* command)
{

    struct scpi_token* args;
  struct scpi_numeric output_numeric;
  unsigned char output_value;
  args = command;
   aftxdata = 6;
  while(args != NULL && args->type == 0)
  {
    args = args->next;
  }

  output_numeric = scpi_parse_numeric(args->value, args->length, 1e3, 0, 25e6);
  if(output_numeric.length == 0)
  {
    
   int sel = (unsigned long)constrain(output_numeric.value, 0, 7);
   //sel = pow(2,sel);
   aftxdata = 6;

      #ifdef debug
   Serial.print("2-TONE");
   // Serial.println(sel);
 
  #endif
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;
    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }

  scpi_free_tokens(command);

  return SCPI_SUCCESS;
}

scpi_error_t AFTX(struct scpi_parser_context* context, struct scpi_token* command)
{

    struct scpi_token* args;
  struct scpi_numeric output_numeric;
  unsigned char output_value;
  args = command;

  while(args != NULL && args->type == 0)
  {
    args = args->next;
  }

  output_numeric = scpi_parse_numeric(args->value, args->length, 1e3, 0, 25e6);
  if(output_numeric.length == 0)
  {
    
   int sel = (unsigned long)constrain(output_numeric.value, 0, 7);
   sel = pow(2,sel);
   aftxdata = sel;

      #ifdef debug
   Serial.print("aftx selected no: ");
    Serial.println(sel);
 
  #endif
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;
    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }

  scpi_free_tokens(command);

  return SCPI_SUCCESS;
}

scpi_error_t RFRX(struct scpi_parser_context* context, struct scpi_token* command)
{

    struct scpi_token* args;
  struct scpi_numeric output_numeric;
  unsigned char output_value;
  args = command;

  while(args != NULL && args->type == 0)
  {
    args = args->next;
  }

  output_numeric = scpi_parse_numeric(args->value, args->length, 1e3, 0, 25e6);
  if(output_numeric.length == 0)
  {
    
   int sel = (unsigned long)constrain(output_numeric.value, 0, 7);
   sel = pow(2,sel);
   rfrxdata = sel;

      #ifdef debug
   Serial.print("RFRX selected no: ");
    Serial.println(sel);
 
  #endif
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;
    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }

  scpi_free_tokens(command);

  return SCPI_SUCCESS;
}

scpi_error_t CPL(struct scpi_parser_context* context, struct scpi_token* command)
{

  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  unsigned char output_value;

  args = command;
  while(args != NULL && args->type == 0)
  {
    args = args->next;
  }

  output_numeric = scpi_parse_numeric(args->value, args->length, 1e3, 0, 25e6);
  if(output_numeric.length == 0 )
  {
    
   int sel  = (unsigned long)constrain(output_numeric.value, 0, 7);
   sel = pow(2,sel);
   #ifdef debug
   Serial.print("coupler selected no: ");
    Serial.println(sel);
  #endif
  cpldata = sel;
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;
    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }

  scpi_free_tokens(command);

  return SCPI_SUCCESS;
}

scpi_error_t enablePTT(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);

  Serial.println("OIC,Signal Generator,1,10");
  return SCPI_SUCCESS;
}

scpi_error_t disablePTT(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);

  Serial.println("OIC,Signal Generator,1,10");
  return SCPI_SUCCESS;
}

void setup_inputs(){

    pinMode(22, INPUT_PULLUP);
    pinMode(23, INPUT_PULLUP);
    pinMode(24, INPUT_PULLUP);
    pinMode(25, INPUT_PULLUP);
    pinMode(26, INPUT_PULLUP);
    pinMode(27, INPUT_PULLUP);
    pinMode(28, INPUT_PULLUP);
    pinMode(29, INPUT_PULLUP);
    pinMode(30, INPUT_PULLUP);
    pinMode(31, INPUT_PULLUP);
    pinMode(32, INPUT_PULLUP);
    pinMode(33, INPUT_PULLUP);
    pinMode(34, INPUT_PULLUP);
    pinMode(35, INPUT_PULLUP);
    pinMode(36, INPUT_PULLUP);
    pinMode(37, INPUT_PULLUP);
    pinMode(38, INPUT_PULLUP);
    pinMode(39, INPUT_PULLUP);
    pinMode(40, INPUT_PULLUP);
    pinMode(41, INPUT_PULLUP);
    pinMode(42, INPUT_PULLUP);
    pinMode(43, INPUT_PULLUP);
    pinMode(44, INPUT_PULLUP);
    pinMode(45, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    
    
  }

scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t local(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t rem(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t setRX(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t SetTX(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t AFRX(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t AFTX(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t CPL(struct scpi_parser_context* context, struct scpi_token* command);


void setup_scpi(){
  
  struct scpi_command* measure;
  struct scpi_command* systems;
  struct scpi_command* route;
  /* First, initialise the parser. */
  scpi_init(&ctx);

  /*
   * After initialising the parser, we set up the command tree.  Ours is
   *
   *  *IDN?         -> identify
   *  *RST          -> reset to local
   *  *LOC
   *  :ROUTe
   *    :AFRX n     ->  
   *    :AFTX n     ->  
   *    :CPL n     -> 
   *  :MEASure
   *    :TEMPerature?   -> get_alltemp
   *  :SYStem
   *    :VOLTage?   -> get_voltage
   */
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "*IDN?", 5, "*IDN?", 5, identify);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "*LOC", 4, "*LOC", 4, local);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "*REM", 4, "*REM", 4, rem);

  route = scpi_register_command(ctx.command_tree, SCPI_CL_CHILD, "ROUTe", 5, "ROUT", 4, NULL);
  measure = scpi_register_command(ctx.command_tree, SCPI_CL_CHILD, "MEASure", 7, "MEAS", 4, NULL);
  systems = scpi_register_command(ctx.command_tree, SCPI_CL_CHILD, "SYStem", 6, "SYS", 3, NULL);


  scpi_register_command(systems, SCPI_CL_CHILD, "RX", 2, "RX", 2, setRX);
  scpi_register_command(systems, SCPI_CL_CHILD, "TX", 2, "TX", 2, setTX);

  scpi_register_command(route, SCPI_CL_CHILD, "2TONE", 5, "2T", 2, tx2tone);
  scpi_register_command(route, SCPI_CL_CHILD, "AFRX", 4, "AFRX", 4, AFRX);
  scpi_register_command(route, SCPI_CL_CHILD, "AFTX", 4, "AFTX", 4, AFTX);
  
  scpi_register_command(route, SCPI_CL_CHILD, "CouPLe", 6, "CPL", 3, CPL);
  scpi_register_command(route, SCPI_CL_CHILD, "RFRX", 4, "RFRX", 4, RFRX);
  
  }
