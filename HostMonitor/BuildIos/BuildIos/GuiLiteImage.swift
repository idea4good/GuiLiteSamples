import UIKit

class GuiLiteImage {
    let width, height, colorBytes : Int
    let buffer: UnsafeMutableRawPointer
    
    init(width: Int, height: Int, colorBytes: Int) {
        self.width = width
        self.height = height
        self.colorBytes = colorBytes
        self.buffer = malloc(width * height * 4)
    }
    
    func getUiImage() -> UIImage?{
        let pixData = (colorBytes == 2) ? getPixelsFrom16bits() : getPixelsFrom32bits()
        if(pixData == nil){
            return nil
        }
        let providerRef = CGDataProvider(data: pixData!)
        let bitmapInfo:CGBitmapInfo = [.byteOrder32Little, CGBitmapInfo(rawValue: CGImageAlphaInfo.noneSkipFirst.rawValue)]
        
        let cgimg = CGImage(width: Int(width), height: height, bitsPerComponent: 8, bitsPerPixel: 32, bytesPerRow: width * 4, space: CGColorSpaceCreateDeviceRGB(), bitmapInfo: bitmapInfo, provider: providerRef!, decode: nil, shouldInterpolate: true, intent: .defaultIntent)
        return UIImage(cgImage: cgimg!)
    }
    
    func getPixelsFrom16bits()->CFData?{
        let rawData = _getUiOfHostMonitor()
        if rawData == nil{
            return nil
        }
        
        for index in 0..<width * height {
            let rgb16 = rawData?.load(fromByteOffset: index * 2, as: UInt16.self)
            let rgb32 = UInt32(rgb16!)
            let color = ((rgb32 & 0xF800) << 8 | ((rgb32 & 0x7E0) << 5) | ((rgb32 & 0x1F) << 3))
            buffer.storeBytes(of: color, toByteOffset: index * 4, as: UInt32.self)
        }
        
        let rawPointer = UnsafeRawPointer(buffer)
        let pixData: UnsafePointer = rawPointer.assumingMemoryBound(to: UInt8.self)
        return CFDataCreate(nil, pixData, width * height * 4)
    }
    
    func getPixelsFrom32bits()->CFData?{
        let rawData = _getUiOfHostMonitor()
        if rawData == nil{
            return nil
        }
        
        let rawPointer = UnsafeRawPointer(rawData)
        let pixData: UnsafePointer = rawPointer!.assumingMemoryBound(to: UInt8.self)
        return CFDataCreate(nil, pixData, width * height * 4)
    }
}
