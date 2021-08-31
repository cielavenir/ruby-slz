require File.expand_path(File.dirname(__FILE__)+'/spec_helper')

describe "slz" do
    it "generates proper deflate stream" do
        io = StringIO.new
        dfl = Slz::Deflate.new
        content = nil
        File.open(File.dirname(__FILE__)+'/10000SalesRecords.csv'){|f|
            content = f.read
            f.rewind
            l = content.size
            siz = 1024
            cnt = (l+siz-1)/siz
            cnt.times{ io.write dfl.deflate(f.read(siz)) }
            io.write dfl.flush
        }
        io.rewind
        p Zlib::Inflate.new(-15).inflate(io.read) == content
    end
end
