#include <wx/wx.h>

/*
holamundo con wxwidgets, tiene implementado sizers.
*/




//clase de la aplicacion.

class MyApp : public wxApp
{
public:
    virtual bool OnInit(); //el sufijo virtual hace un override con la funcion
};

//clase de la ventana, que hereda de la clase wxFrame los metodos publicos y protegidos

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    //aca solo tenemos el constructor de la clase
};

bool MyApp::OnInit()
{
    //declaramos un puntero ventana y usamos el constructor
    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
    //mostramos la ventana.
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    Centre(); //esto centra la ventana en la pantalla

    //creamos un control declarando su puntero, tene su propio constructor, revisar documentacion
    wxPanel * panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel->SetBackgroundColour(wxColor(100, 200, 100));
    //esto setea el color del control

    //esto crea un sizer, se declara como puntero, se le da la direccion
    //margen, comportamiento. revisar documentacion
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND | wxALL, 5);

    this->SetSizerAndFit(sizer);
    //el sizer lo cargamos en el objeto actual

}
//esto es la implementacion de la clase app.
wxIMPLEMENT_APP(MyApp);