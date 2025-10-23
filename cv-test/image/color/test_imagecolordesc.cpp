#include <cassert>
#include <iostream>

#include "imagecolordesc.h"
#include "imagecontext.h"

int main() {
    string imageName = "/home/linye020603/iap-web/cv-test/test-data/image/test-color-band-v.jpg";

    imagecontext* ctx = new imagecontext();
    ctx->desc->setLogLevel(iapcv_log::INFO);

    cout << "Test setDescData: BGR" << endl;
    cout << "Use file: " << imageName << endl;
    if (ctx->reader->read_image(false, imageName)) {
        ctx->desc->setDescData(*ctx->reader->getInputImage(), ColorType::BGR);
        ctx->desc->printMap();
    }
    else {
        cout << "Failed to process image: " << imageName << endl;
    }

    assert(5*350==ctx->desc->countColor(imagecolorvalues::BLACK));
    cout << "Test setDescData: Done." << endl;
    cout << endl;

    // repeat previous action setDescData()
    cout << "Test setDescData BGR: reuse" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setDescData(*ctx->reader->getInputImage(), ColorType::BGR);
    ctx->desc->printMap();
    assert(5*350==ctx->desc->countColor(imagecolorvalues::BLACK));
    cout << "Test setDescData reuse: Done." << endl;
    cout << endl;

    cout << "Test setDescData reuse: change color type" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setDescData(*ctx->reader->getHsvImage(), ColorType::HSV);
    ctx->desc->printMap();
    assert(ColorType::HSV==ctx->desc->getColorType());
    cout << "Test setDescData reuse: change color type Done." << endl;
    cout << endl;

    cout << "Test clear" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->clear();
    color_desc_state* st = new color_desc_state();
    st->s_color_map = ClearableState::just_cleared;
    st->s_color_type = ColorType::HSV;
    st->s_tree_cvt = ClearableState::just_cleared;
    st->s_tree_d3t = ClearableState::just_cleared;
    assert(ctx->desc->verifyState(*st));
    ctx->desc->printState();
    cout << "Test clear: Done." << endl;
    cout << endl;

    cout << "Test set d3tree: Just cleared" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setD3Tree(DimType::HSV, dimensions::HUE);
    assert(ctx->desc->verifyState(*st));
    cout << "Test set d3tree: Just cleared: Done" << endl;

    cout << "Test set d3tree: Just created" << endl;
    cout << "Use file: " << imageName << endl;
    imagecolordesc* desc = new imagecolordesc();
    desc->setD3Tree(DimType::HSV, dimensions::HUE);
    assert(ctx->desc->verifyState(*st));
    delete desc;
    cout << "Test set d3tree: Just created: Done" << endl;

    cout << "Test setDescData BGR: Set HSV tree" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setDescData(*ctx->reader->getInputImage(), ColorType::BGR);
    ctx->desc->printMap();
    ctx->desc->setD3Tree(DimType::HSV, dimensions::HUE);
    ctx->desc->printD3Tree();
    st->s_color_map = ClearableState::just_used;
    st->s_color_type = ColorType::BGR;
    st->s_tree_cvt = ClearableState::just_created;
    st->s_tree_d3t = ClearableState::just_used;
    assert(ctx->desc->verifyState(*st));
    
    cout << "Test setDescData BGR: Set HSV tree: Done." << endl;
    cout << endl;

    cout << "Test color_type BGR. Set BGR tree: BGR-B" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setD3Tree(DimType::BGR, dimensions::B);
    ctx->desc->printD3Tree();
    assert(ctx->desc->verifyState(*st));
    cout << "Test color_type BGR. Set BGR tree: BGR-B Done." << endl;
    cout << endl;

    cout << "Test color_type BGR. Set BGR tree: BGR-G" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setD3Tree(DimType::BGR, dimensions::G);
    ctx->desc->printD3Tree();
    assert(ctx->desc->verifyState(*st));
    cout << "Test color_type BGR. Set BGR tree: BGR-G Done." << endl;
    cout << endl;

    cout << "Test color_type BGR. Set BGR tree: BGR-R" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setD3Tree(DimType::BGR, dimensions::R);
    ctx->desc->printD3Tree();
    assert(ctx->desc->verifyState(*st));
    cout << "Test color_type BGR. Set BGR tree: BGR-R Done." << endl;
    cout << endl;

    cout << "Test setDescData HSV: Set BGR tree" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setDescData(*ctx->reader->getHsvImage(), ColorType::HSV);
    ctx->desc->printMap();
    ctx->desc->setD3Tree(DimType::BGR, dimensions::B);
    ctx->desc->printD3Tree();
    ctx->desc->printState();
    st->s_color_map = ClearableState::just_used;
    st->s_color_type = ColorType::HSV;
    st->s_tree_cvt = ClearableState::just_created;
    st->s_tree_d3t = ClearableState::just_created;
    assert(ctx->desc->verifyState(*st));
    cout << "Test setDescData BGR: Set BGR tree: Done." << endl;
    cout << endl;

    cout << "Test setDescData HSV: Set HSV tree" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setD3Tree(DimType::HSV, dimensions::SAT);
    st->s_color_map = ClearableState::just_used;
    st->s_color_type = ColorType::HSV;
    st->s_tree_cvt = ClearableState::just_created;
    st->s_tree_d3t = ClearableState::just_used;
    assert(ctx->desc->verifyState(*st));
    cout << "Test setDescData HSV: Set HSV tree: Done." << endl;
    cout << endl;

    cout << "Test setDescData HSV: Set XYZ tree" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setD3Tree(DimType::XYZ, dimensions::D_X);
    st->s_color_map = ClearableState::just_used;
    st->s_color_type = ColorType::HSV;
    st->s_tree_cvt = ClearableState::just_created;
    st->s_tree_d3t = ClearableState::just_used;
    assert(ctx->desc->verifyState(*st));
    cout << "Test setDescData HSV: Set XYZ tree: Done." << endl;
    cout << endl;

    cout << "Test setDescData HSV: Set color value tree" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setColorValueTree();
    st->s_color_map = ClearableState::just_used;
    st->s_color_type = ColorType::HSV;
    st->s_tree_cvt = ClearableState::just_used;
    st->s_tree_d3t = ClearableState::just_used;
    assert(ctx->desc->verifyState(*st));
    cout << "Test setDescData HSV: Set color value tree: Done." << endl;
    cout << endl;

    cout << "Test setDescData BGR: Set color value tree" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setDescData(*ctx->reader->getInputImage(), ColorType::BGR);
    ctx->desc->printMap();
    ctx->desc->setColorValueTree();
    ctx->desc->printD3Tree();
    ctx->desc->printState();
    st->s_color_map = ClearableState::just_used;
    st->s_color_type = ColorType::BGR;
    st->s_tree_cvt = ClearableState::just_used;
    st->s_tree_d3t = ClearableState::just_created;
    assert(ctx->desc->verifyState(*st));
    cout << "Test setDescData BGR: Set color value tree: Done." << endl;
    cout << endl;

    cout << "Test setDescData BGR: Set BGR tree" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setD3Tree(DimType::BGR, dimensions::B);
    st->s_color_map = ClearableState::just_used;
    st->s_color_type = ColorType::BGR;
    st->s_tree_cvt = ClearableState::just_used;
    st->s_tree_d3t = ClearableState::just_used;
    assert(ctx->desc->verifyState(*st));
    cout << "Test setDescData HSV: Set BGR tree: Done." << endl;
    cout << endl;

    delete st;
    delete ctx;
    return 0;
}