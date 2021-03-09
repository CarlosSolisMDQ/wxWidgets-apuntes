#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/wxprec.h>
#include <wx/wx.h>

/*
Bien, para que funcione este ejemplo que saque de internet en un solo archivo hay que 
poner cada bloque de codigo de manera estructurada. Si declaras algo tiene que estar 
antes de su implementacion. Alteras el orden y el compilador te tira todo tipo de errores

*/



//primero declaramos las clases leftpanel y rightpanel que van a formar parte de 
//la clase communicate.

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel *parent);
  //el constructor recibe un puntero de el objeto padre
    void OnPlus(wxCommandEvent & event);
    void OnMinus(wxCommandEvent & event);
  //metodos de los botones
    wxButton *m_plus;
    wxButton *m_minus;
    wxPanel *m_parent;
    //tres punteros, dos botones y uno de tipo panel
    int count;

};

class RightPanel : public wxPanel
{
public:
    RightPanel(wxPanel *parent);
    //lo mismo, el constructor recibe un puntero del objeto padre
    void OnSetText(wxCommandEvent & event);
    //el metodo edita el valor de la variable texto
    wxStaticText *m_text;

};

const int ID_PLUS = 101;
const int ID_MINUS = 102;

//se declaran dos ID personalizados para los botones.



class Communicate : public wxFrame
{
public:
    Communicate(const wxString& title);
    LeftPanel *m_lp;
    RightPanel *m_rp;
    wxPanel *m_parent;
  //el constructor recibe como parametro el titulo de la ventana
  //se crean los punteros de los paneles
  //se crea el puntero para almacenar la direccion del objeto padre
};

Communicate::Communicate(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(290, 150))
{
  m_parent = new wxPanel(this, wxID_ANY);
  //creamos el panel padre en memoria
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
  //creamos el sizer
  m_lp = new LeftPanel(m_parent);
  m_rp = new RightPanel(m_parent);
  //creamos los paneles y les pasamos el puntero del objeto communicate como padre
  hbox->Add(m_lp, 1, wxEXPAND | wxALL, 5);
  hbox->Add(m_rp, 1, wxEXPAND | wxALL, 5);
  //agregamos los paneles a sizer que nos da su comportamiento al expandir, el margen...etc.
  m_parent->SetSizer(hbox);
  //seteamos el sizer en el objeto padre.
  this->Centre();
  //centramos
}

LeftPanel::LeftPanel(wxPanel * parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
  count = 0;
  //la variable que almacena la cuenta
  m_parent = parent;
  //el objeto padre
  m_plus = new wxButton(this, ID_PLUS, wxT("+"), 
      wxPoint(10, 10));
  m_minus = new wxButton(this, ID_MINUS, wxT("-"), 
      wxPoint(10, 60));
  //creamos los botones
  Connect(ID_PLUS, wxEVT_COMMAND_BUTTON_CLICKED, 
      wxCommandEventHandler(LeftPanel::OnPlus));
  Connect(ID_MINUS, wxEVT_COMMAND_BUTTON_CLICKED, 
      wxCommandEventHandler(LeftPanel::OnMinus));
  //conectamos el evento.
}

void LeftPanel::OnPlus(wxCommandEvent & WXUNUSED(event))
{
  count++;
//creamos un puntero communicate y le ingresamos la direccion del padre de leftpanel
Communicate *comm = (Communicate *) m_parent->GetParent();
comm->m_rp->m_text->SetLabel(wxString::Format(wxT("%d"), count));
//iteramos entre cada propiedad de el objeto hasta llegar el metodo de edicion heredado de la 
//clase wxPanel.
}

void LeftPanel::OnMinus(wxCommandEvent & WXUNUSED(event))
{
  count--;

  
Communicate *comm = (Communicate *) m_parent->GetParent();
comm->m_rp->m_text->SetLabel(wxString::Format(wxT("%d"), count));
}


RightPanel::RightPanel(wxPanel * parent)
       : wxPanel(parent, wxID_ANY, wxDefaultPosition, 
         wxSize(270, 150), wxBORDER_SUNKEN)
{
    m_text = new wxStaticText(this, -1, wxT("0"), wxPoint(40, 60));
}



class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

    Communicate *communicate = new Communicate(wxT("Widgets communicate"));
    communicate->Show(true);

    return true;
}


