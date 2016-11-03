#ifndef _COM_H_
#define _COM_H_

/*Communication Method Start*/

#define com_met SCREEN_DISPLAY

/*Communication Method End*/

/*Display Adapter Start*/
#if com_met == SCREEN_DISPLAY
    #define DISPLAY_ADAPTER VGA
    #define DISPLAY_ADAPTER_S "VGA"

    #if DISPLAY_ADAPTER == VGA
        #define DISPLAY_ADAPTER_MODE NORMAL_TEXT_MODE
        #define DISPLAY_ADAPTER_MODE_S "NORMAL_TEXT_MODE"
    #endif
#endif
 
/*Display Adapter End*/


#endif /*_COM_H_*/