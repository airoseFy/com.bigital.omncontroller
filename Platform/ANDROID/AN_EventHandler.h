//
//  Application.h
//  Bigital
//
//  Created by bigital on 15/10/23.
//
//

/*----------------------------------------
 |	Includes
 +---------------------------------------*/
#include <jni.h>
#include "EventHandler.h"

class AN_EventHandler:public BaseEventHandler{
public:
	 AN_EventHandler(JNIEnv* env);
	~AN_EventHandler() = default;

protected:
	virtual bool OnLeftButtonDown(int, int) { return false; }
	
	virtual bool OnLeftButtonUp(int, int) { return false; }

	virtual bool OnKeyDown(int, int) { return false; }
	
	virtual bool OnKeyUp(int, int) { return false; }
};

AN_EventHandler::AN_EventHandler(JNIEnv* env)
{
	
}