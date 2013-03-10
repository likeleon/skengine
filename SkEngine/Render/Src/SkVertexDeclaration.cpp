#include "Pch.h"
#include "SkVertexDeclaration.h"
#include "SkLog.h"
#include "SkUtilities.h"
#include "SkD3D9Device.h"

namespace ske
{

	VertexDeclaration::VertexDeclaration()
	: m_vdecl(nullptr)
	{
	}
	
	VertexDeclaration::~VertexDeclaration()
	{
		Destroy();
	}

	bool VertexDeclaration::AddVertexElement(WORD stream, WORD offset, BYTE type, BYTE method, BYTE usage, BYTE usageIndex)
	{
		if (IsCreated())
			return false;

		D3DVERTEXELEMENT9 element;
		element.Stream = stream;
		element.Offset = offset;
		element.Type = type;
		element.Method = method;
		element.Usage = usage;
		element.UsageIndex = usageIndex;
		m_vlayout.push_back(element);
		return true;
	}

	bool VertexDeclaration::Create(D3D9Device& device)
	{
		if (IsCreated() || m_vlayout.empty())
			return false;

		const D3DVERTEXELEMENT9 terminator = D3DDECL_END();
		m_vlayout.push_back(terminator);

		if (!device.CreateVertexDeclaration(&m_vlayout[0], &m_vdecl))
		{
			m_vlayout.pop_back();
			return false;
		}

		m_vlayout.clear();

		SK_ENSURE(IsCreated());
		return true;
	}

	void VertexDeclaration::Destroy()
	{
		SafeRelease(m_vdecl);
		m_vlayout.clear();

		SK_ENSURE(!IsCreated());
	}

	bool VertexDeclaration::IsCreated() const
	{
		return (m_vdecl != nullptr);
	}
}