

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


#define CHANNEL0									0x00
#define CHANNEL1									0x01
#define CHANNEL2									0x02
#define CHANNEL3									0x03
#define CHANNEL4									0x04
#define CHANNEL5									0x05
#define CHANNEL6									0x06
#define CHANNEL7									0x07


extern volatile uint8_t conversionCompleted;

void ADC_Init(void);
void ADC_Select(uint8_t);
uint8_t ADC_isConversionComplete(void);

#endif /* ADC_CONFIG_H_ */