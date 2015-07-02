#ifndef OFX_CT_SHAKE_CANVAS
#define OFX_CT_SHAKE_CANVAS

#include "ofMain.h"

class ofxCTShakeCanvas
{
public:
	ofxCTShakeCanvas()
		:_bAllocate(false)
		,_bShake(false)
		,_iDensityX(10)
		,_iDensityY(10)		
	{}
	~ofxCTShakeCanvas(){}

	void setup(int iWidth = ofGetWidth(), int iHeight = ofGetHeight());
	void update();
	
	void draw();
	void draw(int x, int y);
	void draw(ofPoint pos);

public:
	//inline method
	inline void begin()
	{
		if(_bAllocate)
		{
			_Canvas.begin();
			ofClear(0);
		}
	}
	
	inline void end()
	{
		if(_bAllocate)
		{
			_Canvas.end();
		}
	}
	
	inline void startShake()
	{
		_bShake = true;
	}

	inline void stopShake()
	{
		_bShake = false;
	}

	inline void setDensity(const int x, const int y)
	{
		if(!_bAllocate)
		{
			_iDensityX = x;
			_iDensityY = y;
		}
	}

	inline void setFunc(function<float(void)> func)
	{
		_ShakeFunc = func;
	}

	inline int getWidth()
	{
		return	_Canvas.getWidth();
	}

	inline int getHeight()
	{
		return _Canvas.getHeight();
	}
private:
	void updateMesh();
private:
	bool				_bAllocate;
	bool				_bShake;
	int						_iDensityX, _iDensityY;
	function<float(void)>	_ShakeFunc;

	ofFbo				_Canvas;
	ofMesh				_Mesh;
	vector<ofVec3f>		_VertexSet;
};

#endif // !OFX_CT_SHAKE_CANVAS
