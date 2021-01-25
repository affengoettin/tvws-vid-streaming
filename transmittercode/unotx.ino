void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // from python code
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    const int charlength = Serial.available()+1;
    char mun[charlength];
    memset(mun,0,charlength);
    Serial.readBytes(mun,charlength-1);
    Serial.write(mun);
  }
}
