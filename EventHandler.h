//
//  Application.h
//  Bigital
//
//  Created by bigital on 15/10/23.
//
//

/*-----------------------------------------------
|	Includes
+----------------------------------------------*/
#include "Log.h"

#define 	MOUSE_LEFT_BUTTON_DOWN			0
#define		MOUSE_LEFT_BUTTON_UP			1
#define 	MOUSE_MOVE						2
#define 	KEY_DOWN						3
#define		KEY_UP							4

class IEventHandler{
protected:
	virtual ~IEventHandler() = default;
	
public:
	virtual bool operator() (int , int , int) = 0;
};

class BaseEventHandler{
protected:
	virtual ~BaseEventHandler() = default;
	
	virtual bool OnLeftButtonDown(int, int) = 0;
	
	virtual bool OnLeftButtonUp(int, int) = 0;

	virtual bool OnKeyDown(int, int) = 0;
	
	virtual bool OnKeyUp(int, int) = 0;
	
	virtual bool OnMouseEvent(int type, int code, int value)
	{
		bool ret = false;
		
		switch(type){
			case MOUSE_LEFT_BUTTON_DOWN:
				ret = this->OnLeftButtonDown(code, value);
				break;
			case MOUSE_LEFT_BUTTON_UP:
				ret = this->OnLeftButtonUp(code, value);
				break;
			default:
				break;
		}
		
		return ret;
	}
	
	virtual bool OnKeyEvent(int type, int code, int value)
	{
		bool ret = false;
		
		switch(type){
			case KEY_DOWN:
				ret = this->OnKeyDown(code, value);
				break;
			case KEY_UP:
				ret = this->OnKeyUp(code, value);
				break;
			default:
				break;
		}
		
		return ret;
	}
	
public:	
	virtual bool operator() (int type, int code, int value) 
	{
		debug("BaseEventHandler", "OnEvent type = %d, code = %d, value = %d", type, code, value);
		bool ret = false;
		
		switch(type){
			case MOUSE_LEFT_BUTTON_DOWN:
			case MOUSE_LEFT_BUTTON_UP:
			case MOUSE_MOVE:
				ret = this->OnMouseEvent(type, code, value);
				break;
			case KEY_DOWN:
			case KEY_UP:
				ret = this->OnKeyEvent(type, code, value);
				break;
			default:
				break;
		}
		
		return ret;
	}
};