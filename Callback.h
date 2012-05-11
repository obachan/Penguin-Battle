//  Callback.h

#if !defined(CALLBACK_H)
#define CALLBACK_H


class cCallback
{
	public:
		virtual bool Execute(void *Param) const =0;
};


template <class cInstance>
class TCallback : public cCallback // Inheriting
{
	public:
		TCallback() // constructor
		{
			// Important : zeroing the pointer so we later can check for errors
			pFunction = 0;
		}

		// (You can change the callback to take more parameters or to return something)
		typedef bool (cInstance::*tFunction)(void *Param);
		
		// Execute the Callback
		virtual bool Execute(void *Param) const 
		{
			if (pFunction) return (cInst->*pFunction)(Param);
			else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		// Set or change the Callback
		void SetCallback (cInstance  *cInstancePointer, 
						  tFunction   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction = pFunctionPointer;
		}

	private:
		cInstance  *cInst;
		tFunction  pFunction;
};

#endif // CALLBACK_H




