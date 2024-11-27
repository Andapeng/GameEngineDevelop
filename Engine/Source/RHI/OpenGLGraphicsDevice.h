#include "IGraphicsDevice.h"
class OpenGLGraphicsDevice : public IGraphicsDevice
{
public:
	OpenGLGraphicsDevice();
	~OpenGLGraphicsDevice();

	void Initialize() override;
	void Release() override;
	void Draw() override;
private:
};