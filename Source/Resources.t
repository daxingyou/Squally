﻿<#@ template debug="false" hostspecific="true" language="C#" #>
<#@ assembly name="System.Core" #>
<#@ import namespace="System.IO" #>
<#@ import namespace="System.Linq" #>
<#@ import namespace="System.Text" #>
<#@ import namespace="System.Collections.Generic" #>
<#@ output extension=".cpp" #>
<#
WriteLine("///////////////////////////////////////////////////////////////////////////////////////////////");
WriteLine("// THIS C++ FILE IS GENERATED DO NOT EDIT. MAKE CHANGES IN THE RESOURCE TEXT TEMPLATING FILE //");
WriteLine("///////////////////////////////////////////////////////////////////////////////////////////////");
WriteLine("");
WriteLine("#include \"Resources.h\"");
WriteLine("#include <string>");
WriteLine("");

foreach (string file in Directory.EnumerateFiles(this.Host.ResolvePath("../Resources"), "*.*", SearchOption.AllDirectories))
{
	if (!file.EndsWith(".png") &&
		!file.EndsWith(".jpg") &&
		!file.EndsWith(".bmp") &&
		!file.EndsWith(".tif") &&
		!file.EndsWith(".ttf") &&
		!file.EndsWith(".frag") &&
		!file.EndsWith(".vert") &&
		!file.EndsWith(".mp3") &&
		!file.EndsWith(".wav") &&
		!file.EndsWith(".plist") &&
		!file.EndsWith(".json") &&
		!file.EndsWith(".tmx")) {
			continue;
		}
		
	string variableName = Path.GetFileNameWithoutExtension(file.Replace(this.Host.ResolvePath("../Resources"), "").TrimStart('\\').Replace(@"\", "_").Replace(" ", "_").Replace("-", "_").Replace("(", "_").Replace(")", "_"));
	string relativeFilePath = file.Replace(this.Host.ResolvePath("../Resources"), "").TrimStart('\\').Replace(@"\", @"\\");

	WriteLine("const std::string Resources::" + variableName + " = \"" + relativeFilePath + "\";");
}
#>