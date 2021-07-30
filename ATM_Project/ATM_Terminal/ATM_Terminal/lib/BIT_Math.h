/**
 * @file BIT_Math.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef BitMath_H_
#define BitMath_H_


#define SETBIT(R,B) (R|=(1<<B))
#define CLRBIT(R,B) (R&=~(1<<B))
#define TGLBIT(R,B) (R^=(1<<B))
#define GETBIT(R,B) ((R>>B)&0x01)



#define SET_BIT(VAR,BIT)          	  	VAR |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT)        	  	VAR &= ~(1 << (BIT))
#define CLEAR_BIT(VAR,BIT)         	  	VAR &= ~(1 << (BIT))

#define GET_BIT(VAR,BIT)          		((VAR >> BIT) & 1  )
#define TOG_BIT(VAR,BIT)          		VAR ^=  (1 << (BIT))

/*check if a specified Bit is Set*/
#define BIT_IS_SET(REG,BIT)      		((REG>>BIT)&1)
/*Check if a specified BIT is Clear*/
#define BIT_IS_CLEAR(REG,BIT)  			(!((REG>>BIT)&1))



#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)  CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0



#endif /* BitMath_H_*/
