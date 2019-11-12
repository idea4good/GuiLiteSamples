import Cocoa

class GuiLiteView: NSView {
    var viewWidth: Int?
    var viewHeight: Int?
    var isMouseDown = false
    
    func setSize(width: Int, height: Int){
        self.viewWidth = width
        self.viewHeight = height
    }
    override func draw(_ dirtyRect: NSRect) {
        let img = getUiImage()
        if(img == nil) {
            return
        }
        
        super.draw(dirtyRect)
        // Drawing code here.
        let bg = NSColor.init(patternImage: img!)
        bg.setFill()
        self.bounds.fill()
    }
    
    override func mouseUp(with event: NSEvent) {
        self.isMouseDown = false;
        let pos = NSEvent.mouseLocation
        mouse_up(Int32(pos.x), Int32(viewHeight! - Int(pos.y)))
    }
    
    override func mouseDown(with event: NSEvent) {
        self.isMouseDown = true;
        let pos = NSEvent.mouseLocation
        mouse_down(Int32(pos.x), Int32(viewHeight! - Int(pos.y)))
    }
    
    override func mouseDragged(with event: NSEvent) {
        if self.isMouseDown{
            let pos = NSEvent.mouseLocation
            mouse_down(Int32(pos.x), Int32(viewHeight! - Int(pos.y)))
        }
    }

    func getUiImage() -> NSImage?{
        let pixData = getPixelsFrom32bits()
        if(pixData == nil){
            return nil
        }
        let providerRef = CGDataProvider(data: pixData!)
        let bitmapInfo:CGBitmapInfo = [.byteOrder32Little, CGBitmapInfo(rawValue: CGImageAlphaInfo.noneSkipFirst.rawValue)]
        
        let cgimg = CGImage(width: viewWidth!, height: viewHeight!, bitsPerComponent: 8, bitsPerPixel: 32, bytesPerRow: viewWidth! * 4, space: CGColorSpaceCreateDeviceRGB(), bitmapInfo: bitmapInfo, provider: providerRef!, decode: nil, shouldInterpolate: true, intent: .defaultIntent)
        return NSImage(cgImage: cgimg!, size: CGSize(width: viewWidth!, height: viewHeight!))
    }
    
    func getPixelsFrom32bits()->CFData?{
        let rawData = _getUiOfHostMonitor()
        if rawData == nil{
            return nil
        }
        
        let rawPointer = UnsafeRawPointer(rawData)
        let pixData: UnsafePointer = rawPointer!.assumingMemoryBound(to: UInt8.self)
        return CFDataCreate(nil, pixData, viewWidth! * viewHeight! * 4)
    }
}
