function isNumberKey(evt){
    var charCode = (evt.which) ? evt.which : event.keyCode
    if (charCode > 31 && (charCode < 48 || charCode > 57))
        return false;
    return true;
}

function createMap()
{
	var x=document.getElementById('width').value;
	var y=document.getElementById('height').value;
	var stringa="<table id='tabella'>";
	for(i=0;i<y;i++)
	{
		stringa+="<tr>";
		for(j=0;j<x;j++)
			stringa+="<td id='a"+(i*x+j)+"' onclick='draw("+(i*x+j)+")'>	</td>";
		stringa+="</tr>";
	}
	document.getElementById("map").innerHTML=stringa;
	
	//Dinamico
	parseDom()
	return;
	
}

function addTexture()
{
	var src=document.getElementById('directory').value;
	var name=document.getElementById('name').value;
	var node=document.createElement("img");
	var x=document.getElementById("palette");
	x.appendChild(node);
	x.lastChild.setAttribute('src',src);
	x.lastChild.setAttribute('id',name);
}

function draw(n)
{
	
	document.getElementById("a"+n).className=document.getElementById('Scelta').innerHTML;
	//dinamico
	parseDom()
	//prompt("Nome file xml","Pissa "+n);


}

function changeTexture(nome)
{
	document.getElementById('Scelta').innerHTML=nome;

}

function parseDom()
{
		stringa="<?xml version=”1.0″ ?>\n";
		var top=document.getElementById('tabella');
		var righe=top.rows;
		var colonne;
		for(i=0;i<righe.length;i++)
		{
			colonne=righe[i].childNodes;
			for(j=0;j<colonne.length;j++)
			{
				stringa+=getStringa(colonne[j])+" \n";
				//stringa+="<tile src='"+colonne[j].getAttribute("class")+"'>\n";
			}
		
		}
		document.getElementById('xml').innerHTML=stringa; 

}



function getStringa(tile)
{
	var sottostringa=tile.className.substring(0,4);
	var output="<tile src='"+tile.getAttribute("class")+"'";
	if(sottostringa=="door")
		output+=" destination='"+tile.getAttribute(name)+"'";
	else if(sottostringa=="wall")
			output+=" block='true'";
	else
		output+=" block='false'";
	output+=" />";
	return output;
}
