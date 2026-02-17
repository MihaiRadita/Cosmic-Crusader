#pragma once

#include "stdafx.h"

template<typename T>
class EnumMask
{
public:
	void setValue(const int value)
	{
		m_value = value;
	}

	void addValue(const T enumValue)
	{
		m_value |= static_cast<int>(std::pow(2, static_cast<int>(enumValue)));
	}

	bool hasValue(const T enumValue) const
	{
		return (m_value & static_cast<int>(std::pow(2, static_cast<int>(enumValue)))) != 0;
	}

	void resetValue()
	{
		m_value = 0;
	}

	int getRawValue()
	{
		return m_value;
	}

	std::vector<T> getValueList(const int enumElementCount) const
	{
		std::vector<T> valueList;
		for (int enumIntVal = 0; enumIntVal < enumElementCount; enumIntVal++)
		{
			T enumVal = static_cast<T>(enumIntVal);
			if (hasValue(enumVal))
			{
				valueList.emplace_back(enumVal);
			}
		}

		return valueList;
	}

private:

	int m_value = 0;
};

