// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include "cppcodestylepreferences.h"
#include "cppeditorconstants.h"

using namespace Utils;

namespace CppEditor {

CppCodeStylePreferences::CppCodeStylePreferences(QObject *parent) :
    ICodeStylePreferences(parent)
{
    setSettingsSuffix("CodeStyleSettings");
    setGlobalSettingsCategory(Constants::CPP_CODE_STYLE_SETTINGS_ID);
}

QVariant CppCodeStylePreferences::value() const
{
    QVariant v;
    v.setValue(codeStyleSettings());
    return v;
}

void CppCodeStylePreferences::setValue(const QVariant &data)
{
    if (!data.canConvert<CppCodeStyleSettings>())
        return;

    setCodeStyleSettings(data.value<CppCodeStyleSettings>());
}

CppCodeStyleSettings CppCodeStylePreferences::codeStyleSettings() const
{
    return m_data;
}

void CppCodeStylePreferences::setCodeStyleSettings(const CppCodeStyleSettings &data)
{
    if (m_data == data)
        return;

    m_data = data;

    QVariant v;
    v.setValue(data);
    emit valueChanged(v);
    if (!currentDelegate())
        emit currentValueChanged(v);
}

CppCodeStyleSettings CppCodeStylePreferences::currentCodeStyleSettings() const
{
    QVariant v = currentValue();
    if (!v.canConvert<CppCodeStyleSettings>()) {
        // warning
        return {};
    }
    return v.value<CppCodeStyleSettings>();
}

Store CppCodeStylePreferences::toMap() const
{
    Store map = ICodeStylePreferences::toMap();
    if (!currentDelegate()) {
        const Store dataMap = m_data.toMap();
        for (auto it = dataMap.begin(), end = dataMap.end(); it != end; ++it)
            map.insert(it.key(), it.value());
    }
    return map;
}

void CppCodeStylePreferences::fromMap(const Store &map)
{
    ICodeStylePreferences::fromMap(map);
    if (!currentDelegate())
        m_data.fromMap(map);
}

} // namespace CppEditor
