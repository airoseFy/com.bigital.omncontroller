//
//  Context.h
//  Platinum
//
//  Created by apple on 15/10/2.
//
//

#ifndef _CONTEXT_H_
#define _CONTEXT_H_

class IContext{
public:
    virtual ~IContext() = default;
    
    virtual void Initailization(void* ) = 0;
    virtual void Release() = 0;
};

#endif /* _CONTEXT_H_ */
