#pragma once

#include "SkNonCopyable.h"
#include <d3dx9.h>
#include <string>
#include <map>

namespace ske
{
	class D3D9Device;
	class Matrix4;
	class Vector4;
	class Texture;

	class D3DEffect : private NonCopyable
	{
	public:
		D3DEffect() : m_effect(nullptr), m_techBegun(false) {}
		~D3DEffect() { Destroy(); }

		bool Create(D3D9Device &device, const std::wstring& effectFile);
		void Destroy();
		bool IsCreated() const;

		bool SetTechnique(const std::string& techName);
		bool Begin(unsigned int &numPass);
		bool End();
		bool BeginPass(unsigned int pass);
		bool EndPass();

		// Effect parameter
		class Parameter
		{
		public:
			Parameter();
			bool SetValue(const Matrix4& m);
			bool SetValue(const Vector4& v);
			bool SetValue(const Texture& texture);

		private:
			D3DEffect* m_d3dEffect;
			D3DXHANDLE m_handle;

			friend class D3DEffect;
		};
		Parameter* GetParameter(const std::string& paramName);

	private:
		LPD3DXEFFECT m_effect;
		typedef std::map<std::string, Parameter> Parameters;
		Parameters m_params;
		bool m_techBegun;
	};
}