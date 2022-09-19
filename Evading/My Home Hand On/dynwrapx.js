
function WriteHexToFile(hex, fileName){
	// Codepage conversion table
	var _c=[199,252,233,226,228,224,229,231,234,235,232,239,238,236,196,197,201,230,198,244,246,242,251,249,255,214,220,162,163,165,8359,402,225,237,243,250,241,209,170,186,191,8976,172,189,188,161,171,187,9617,9618,9619,9474,9508,9569,9570,9558,9557,9571,9553,9559,9565,9564,9563,9488,9492,9524,9516,9500,9472,9532,9566,9567,9562,9556,9577,9574,9568,9552,9580,9575,9576,9572,9573,9561,9560,9554,9555,9579,9578,9496,9484,9608,9604,9612,9616,9600,945,223,915,960,931,963,181,964,934,920,937,948,8734,966,949,8745,8801,177,8805,8804,8992,8993,247,8776,176,8729,183,8730,8319,178,9632,160]

    for (string = '', c = 0; c < hex.length; c += 2){
       	var i = parseInt(hex.substr(c, 2), 16);
       	string += String.fromCharCode( (i<128) ? i : _c[i-128] );
    }

    var stream = new ActiveXObject('ADODB.Stream');
    stream.Type = 2;
    stream.CharSet = '437';
    stream.Open();
    stream.WriteText(string);
    stream.SaveToFile(fileName, 2);
    stream.Close();
}

var outPath = "";
var outFile = "";
var hexEncoded = "";

WriteHexToFile(hexEncoded, outPath + outFile);

var manifest = "<?xml version=\"1.0\" encoding=\"UTF-16\" standalone=\"yes\"?>";
manifest += "<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">";
manifest += "<file name=\"" + outFile + "\" loadFrom=\"" + outPath + "\" >";
manifest += "<comClass clsid=\"{89565276-A714-4A43-912E-978B935EDCCC}\" progid=\"*UpdateMe*\" threadingModel=\"Both\" />";
manifest += "</file>";
manifest += "</assembly>";

var ctx = new ActiveXObject("Microsoft.Windows.ActCtx");
ctx.Manifest = "dynwrapx.manifest";
var wrapper = ctx.CreateObject("DynamicWrapperX");
wrapper.Register("user32.dll", "MessageBoxW", "i=hwwu", "r=l");
wrapper.MessageBoxW(0, "Hello", "Test", 0);
var obj = ctx.CreateObject();

