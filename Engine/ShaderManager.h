////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderManager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "DirectX11.h"
#include "TextureShader.h"
#include "LightShader.h"
#include "BumpmapShader.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManager
////////////////////////////////////////////////////////////////////////////////
class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderTextureShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*);

	bool RenderLightShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*,
		XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);

	bool RenderBumpMapShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);

private:
	TextureShader* m_TextureShader;
	LightShader* m_LightShader;
	BumpmapShader* m_BumpMapShader;
};

#endif