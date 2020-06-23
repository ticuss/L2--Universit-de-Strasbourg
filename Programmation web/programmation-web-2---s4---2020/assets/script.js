

var button=document.getElementById("submit");
var format = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;


function validationContactForm (){
    var elmnt = document.getElementById("email");
    
    var nom=document.getElementById("fname");
    
    var desc = document.getElementById("subject");
  


	if (format.test(document.getElementById("email").value))
	{	
                
	}
	else
	{		
        
        elmnt.placeholder="E-mail invalide";
        elmnt.style.color = "red";
        elmnt.style.fontWeight = "bold";
        return false;
        
    }

    if(desc.value.length == 0){
        
        desc.placeholder="Description obligatoire" ;
        desc.style.color = "red";
        desc.style.fontWeight = "bold";
        return false;
        
    }
    if(nom.value.length == 0){
        
        nom.placeholder="Champ obligatoire";
        nom.style.color = "red";
        nom.style.fontWeight = "bold";
        return false;
        
    }
    
    if(true){
        alert("Merci pour votre reponse ");
    }
}


$.getJSON("lang.json", function(json){
    
    if(!localStorage.getItem("lang")){
      localStorage.setItem("lang", "fr");
    }
    var lang = localStorage.getItem("lang");
    var doc = json;
    $('.lang').each(function(index, element){
      $(this).text(doc[lang][$(this).attr('key')]);
    });
  
    $('.translate').click(function(){
      localStorage.setItem("lang", $(this).attr('id')) ;
      var lang = $(this).attr('id');
      var doc = json;
        $('.lang').each(function(index, element){
          $(this).text(doc[lang][$(this).attr('key')]);
        }); 
    }); 
  });

