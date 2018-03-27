////////////////////////////////////////////////////////////////////////////////
// Filename: Model.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11_1.h>
#include <DirectXMath.h> 
using namespace DirectX;

#include <fstream>
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Texture.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Model
////////////////////////////////////////////////////////////////////////////////
class Model
{
private:
	struct VertexType
	{
		XMFLOAT3  position;
		XMFLOAT2  texture;
		XMFLOAT3  normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	Texture* m_Texture;
	ModelType* m_model;
};

#endif