/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU

http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "stdneb.h"
#include "vegetation/VegetationServer.h"
#include "vegetation/InstanceMap.h"

namespace Vegetation
{
	using namespace Serialization;

	const char* s_TemplateInstMapCount = "TemplateInstMapCount";
	const char* s_TemplateInstMapName = "TemplateInstMapName";

	class VegetationInstanceContainerSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( VegetationInstanceContainer* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(VegetationInstanceContainer* obj, SerializeReader* pReader)
		{
			SizeT count;
			pReader->SerializeInt(s_TemplateInstMapCount, count );
			if ( count != 0 )
			{
				obj->mContainer.BeginBulkAdd();
				for ( IndexT index = 0; index < count; ++index )
				{
					Util::String name;
					pReader->SerializeString(s_TemplateInstMapName, name );
					GPtr<VegeInstanceMap> vegeInst = pReader->SerializeObject<VegeInstanceMap>();

				}
				obj->mContainer.EndBulkAdd();
			}


		}
		//------------------------------------------------------------------------
		void Save( const VegetationInstanceContainer* obj, SerializeWriter* pWriter )
		{
			SizeT count = obj->mContainer.Size();

			pWriter->SerializeInt(s_TemplateInstMapCount, count );
			for ( IndexT index = 0; index < count; ++index )
			{
				const Util::StringAtom& name = obj->mContainer.KeyAtIndex( index );
				const VegeInstanceMapPtr& vegeObj = obj->mContainer.ValueAtIndex( index ); 
				pWriter->SerializeString(s_TemplateInstMapName, name.AsString() );
				pWriter->SerializeObject( vegeObj );
			}
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion VegetationInstanceContainer::GetVersion() const
	{
		return 1;	//	current version is 1
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void VegetationInstanceContainer::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		VegetationInstanceContainerSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void VegetationInstanceContainer::Save( SerializeWriter* pWriter ) const
	{
		VegetationInstanceContainerSerialization Serialize;
		Serialize.Save( this, pWriter );
	}


}