////////////////////////////////////////////////////////////////////////////////
// Filename: Texture.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Texture.h"


Texture::Texture()
{
	m_texture = 0;
}


Texture::Texture(const Texture& other)
{
}


Texture::~Texture()
{
}


bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;


	// Load the texture in.
	result = CreateDDSTextureFromFile(device, filename, NULL, &m_texture, NULL);

	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void Texture::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_texture;

}