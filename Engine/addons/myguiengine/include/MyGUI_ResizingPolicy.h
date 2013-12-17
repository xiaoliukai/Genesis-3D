/*!
	@file
	@author		Albert Semenov
	@date		12/2010
*/
/*
	This file is part of MyGUI.

	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __MYGUI_RESIZING_POLICY_H__
#define __MYGUI_RESIZING_POLICY_H__

#include "MyGUI_Prerequest.h"

namespace MyGUI
{

	struct MYGUI_EXPORT ResizingPolicy
	{
		enum Enum
		{
			Auto,
			Fixed,
			Fill,
			MAX
		};

		ResizingPolicy(Enum _value = MAX) :
			value(_value)
		{
		}

		static ResizingPolicy parse(const std::string& _value)
		{
			ResizingPolicy type;
			int value = 0;
			while (true)
			{
				const char* name = type.getValueName(value);
				if (strcmp(name, "") == 0 || name == _value)
					break;
				value++;
			}
			type.value = Enum(value);
			return type;
		}

		friend bool operator == (ResizingPolicy const& a, ResizingPolicy const& b)
		{
			return a.value == b.value;
		}

		friend bool operator != (ResizingPolicy const& a, ResizingPolicy const& b)
		{
			return a.value != b.value;
		}

		friend std::ostream& operator << (std::ostream& _stream, const ResizingPolicy&  _value)
		{
			_stream << _value.getValueName(_value.value);
			return _stream;
		}

		friend std::istream& operator >> (std::istream& _stream, ResizingPolicy&  _value)
		{
			std::string value;
			_stream >> value;
			_value = parse(value);
			return _stream;
		}

		std::string print() const
		{
			return getValueName(value);
		}

	private:
		const char* getValueName(int _index) const
		{
			static const char* values[MAX + 1] = { "Auto", "Fixed", "Fill", "" };
			return values[(_index < MAX && _index >= 0) ? _index : MAX];
		}

	private:
		Enum value;
	};

} // namespace MyGUI

#endif // __MYGUI_RESIZING_POLICY_H__
