// #include "materialManager.h"
// #include "room.h"
// #include "tri.h"

// Room::Room()
// {
//     init();
//     // refine();
//     // refine();
//     // refine();
//     // refine();
//     // refine();
//     // refine();
//     // refine();
//     // refine();
// }

// std::vector<std::shared_ptr<Geometry>> Room::getTris() const
// {
//     return m_tris;
// }

// //a tri follows anti clockwise rule
// void Room::init()
// {
//     float hw = 100;
//     float depth = 400;

//     // front left
//     TriVertex a_fl(hw, hw, depth);
//     TriVertex b_fl(hw, -hw, depth);
//     TriVertex c_fl(-hw, hw, depth);
//     std::shared_ptr<Tri> fl = std::make_shared<Tri>(a_fl, b_fl, c_fl, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
//     m_tris.push_back(fl);

//     // front right
//     TriVertex a_fr(-hw, -hw, depth);
//     TriVertex b_fr(-hw, hw, depth);
//     TriVertex c_fr(hw, -hw, depth);
//     std::shared_ptr<Tri> fr = std::make_shared<Tri>(a_fr, b_fr, c_fr, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
//     m_tris.push_back(fr);

//     // left near
//     TriVertex a_ln(hw, -hw, -depth);
//     TriVertex b_ln(hw, -hw, depth);
//     TriVertex c_ln(hw, hw, -depth);
//     std::shared_ptr<Tri> ln = std::make_shared<Tri>(a_ln, b_ln, c_ln, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));
//     m_tris.push_back(ln);

//     // left far
//     TriVertex a_lf(hw, hw, depth);
//     TriVertex b_lf(hw, hw, -depth);
//     TriVertex c_lf(hw, -hw, depth);
//     std::shared_ptr<Tri> lf = std::make_shared<Tri>(a_lf, b_lf, c_lf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));
//     m_tris.push_back(lf);

//     // right near
//     TriVertex a_rn(-hw, -hw, -depth);
//     TriVertex b_rn(-hw, hw, -depth);
//     TriVertex c_rn(-hw, -hw, depth);
//     std::shared_ptr<Tri> rn = std::make_shared<Tri>(a_rn, b_rn, c_rn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
//     m_tris.push_back(rn);

//     // right far
//     TriVertex a_rf(-hw, hw, depth);
//     TriVertex b_rf(-hw, -hw, depth);
//     TriVertex c_rf(-hw, hw, -depth);
//     std::shared_ptr<Tri> rf = std::make_shared<Tri>(a_rf, b_rf, c_rf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
//     m_tris.push_back(rf);

//     // bottom near
//     TriVertex a_bn(hw, -hw, -depth);
//     TriVertex b_bn(-hw, -hw, -depth);
//     TriVertex c_bn(hw, -hw, depth);
//     std::shared_ptr<Tri> bn = std::make_shared<Tri>(a_bn, b_bn, c_bn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
//     m_tris.push_back(bn);

//     // bottom far
//     TriVertex a_bf(-hw, -hw, depth);
//     TriVertex b_bf(hw, -hw, depth);
//     TriVertex c_bf(-hw, -hw, -depth);
//     std::shared_ptr<Tri> bf = std::make_shared<Tri>(a_bf, b_bf, c_bf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
//     m_tris.push_back(bf);

//     // top near
//     TriVertex a_tn(hw, hw, -depth);
//     TriVertex b_tn(hw, hw, depth);
//     TriVertex c_tn(-hw, hw, -depth);
//     std::shared_ptr<Tri> tn = std::make_shared<Tri>(a_tn, b_tn, c_tn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_BLUE));
//     m_tris.push_back(tn);

//     // top far
//     TriVertex a_tf(-hw, hw, depth);
//     TriVertex b_tf(-hw, hw, -depth);
//     TriVertex c_tf(hw, hw, depth);
//     std::shared_ptr<Tri> tf = std::make_shared<Tri>(a_tf, b_tf, c_tf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_BLUE));
//     m_tris.push_back(tf);

//     // back left
//     TriVertex a_bl(hw, hw, -depth);
//     TriVertex b_bl(-hw, hw, -depth);
//     TriVertex c_bl(hw, -hw, -depth);
//     std::shared_ptr<Tri> bl = std::make_shared<Tri>(a_bl, b_bl, c_bl, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_WHITE));
//     m_tris.push_back(bl);

//     // back right
//     TriVertex a_br(-hw, -hw, -depth);
//     TriVertex b_br(hw, -hw, -depth);
//     TriVertex c_br(-hw, hw, -depth);
//     std::shared_ptr<Tri> br = std::make_shared<Tri>(a_br, b_br, c_br, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_WHITE));
//     m_tris.push_back(br);
// }

// void Room::refine()
// {
//     //later...
    
//     // std::vector<Geometry*> v;

//     // for(auto it = m_tris.begin(); it != m_tris.end(); it++)
//     // {
//     //     Tri* a = new Tri();
//     //     Tri *b = new Tri();
//     //     Tri *c = new Tri();

//     //     ((Tri*)(*it))->getSplitChildren(a,b,c);

//     //     v.push_back(a);
//     //     v.push_back(b);
//     //     v.push_back(c);

//     //     delete (*it);
//     // }

//     // m_tris.clear();
//     // m_tris = v;
// }
