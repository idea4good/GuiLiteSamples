//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//

#ifndef Bridging_Header
#define Bridging_Header

#ifdef __cplusplus
extern "C"{
#endif

    void _startHostMonitor(int width, int height, int colorBytes);
    void* _getUiOfHostMonitor();
    void mouse_down(int x, int y);
    void mouse_up(int x, int y);
    
#ifdef __cplusplus
}
#endif
#endif /* native_hpp */
