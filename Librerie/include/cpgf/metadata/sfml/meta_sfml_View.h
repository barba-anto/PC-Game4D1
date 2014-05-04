/*
  cpgf Library
  Copyright (C) 2011 - 2013 Wang Qi http://www.cpgf.org/
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/


// Auto generated file, don't modify.

#ifndef __META_SFML_VIEW_H
#define __META_SFML_VIEW_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace sf;


namespace meta_sfml { 


template <typename D>
void buildMetaClass_View(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const FloatRect &)>()
        ._default(copyVariantFromCopyable(FloatRect(0, 0, 1000, 1000)))
    ;
    _d.CPGF_MD_TEMPLATE _constructor<void * (const sf::Vector2f &, const sf::Vector2f &)>();
    _d.CPGF_MD_TEMPLATE _method("SetCenter", (void (D::ClassType::*) (float, float))&D::ClassType::SetCenter);
    _d.CPGF_MD_TEMPLATE _method("SetCenter", (void (D::ClassType::*) (const sf::Vector2f &))&D::ClassType::SetCenter);
    _d.CPGF_MD_TEMPLATE _method("SetHalfSize", (void (D::ClassType::*) (float, float))&D::ClassType::SetHalfSize);
    _d.CPGF_MD_TEMPLATE _method("SetHalfSize", (void (D::ClassType::*) (const sf::Vector2f &))&D::ClassType::SetHalfSize);
    _d.CPGF_MD_TEMPLATE _method("SetFromRect", &D::ClassType::SetFromRect);
    _d.CPGF_MD_TEMPLATE _method("GetCenter", &D::ClassType::GetCenter);
    _d.CPGF_MD_TEMPLATE _method("GetHalfSize", &D::ClassType::GetHalfSize);
    _d.CPGF_MD_TEMPLATE _method("GetRect", &D::ClassType::GetRect);
    _d.CPGF_MD_TEMPLATE _method("Move", (void (D::ClassType::*) (float, float))&D::ClassType::Move);
    _d.CPGF_MD_TEMPLATE _method("Move", (void (D::ClassType::*) (const sf::Vector2f &))&D::ClassType::Move);
    _d.CPGF_MD_TEMPLATE _method("Zoom", &D::ClassType::Zoom);
}


} // namespace meta_sfml




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
