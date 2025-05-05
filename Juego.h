#pragma once
#include "Controladora.h";

namespace Bomberman {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Juego
	/// </summary>
	public ref class Juego : public System::Windows::Forms::Form
	{
	public:
		CControladora* controladora = new CControladora();
		Bitmap^ bmpPiso = gcnew Bitmap("Imagenes\\piso1.png");
		Bitmap^ bmpIrrompible = gcnew Bitmap("Imagenes\\irrompible1.png");
		Bitmap^ bmpRrompible = gcnew Bitmap("Imagenes\\rrompible1.png");
		Bitmap^ bmpJugador = gcnew Bitmap("Imagenes\\protagonista1.png");

		Juego(void)
		{
			bmpJugador->MakeTransparent(bmpJugador->GetPixel(0, 0));
			InitializeComponent();
			//
			//TODO: agregar c�digo de constructor aqu�
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se est�n usando.
		/// </summary>
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// Variable del dise�ador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�todo necesario para admitir el Dise�ador. No se puede modificar
		/// el contenido de este m�todo con el editor de c�digo.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(342, 316);
			this->Name = L"Juego";
			this->Text = L"Juego";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Juego::FormLoad);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::TeclaKeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::TeclaKeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);
		
		controladora->dibujarCancha(buffer->Graphics, bmpPiso, bmpIrrompible, bmpRrompible);
		controladora->moverJugador(buffer->Graphics, bmpJugador);
		
		buffer->Render(g);

		delete buffer, espacio, g;
	}
	private: System::Void FormLoad(System::Object^ sender, System::EventArgs^ e) {
		controladora->Dibujar();
	}

	private: System::Void TeclaKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Up:
			controladora->getJugador()->setDireccion(EDireccion::Arriba);
			break;
		case Keys::Down:
			controladora->getJugador()->setDireccion(EDireccion::Abajo);
			break;
		case Keys::Left:
			controladora->getJugador()->setDireccion(EDireccion::Izquierda);
			break;
		case Keys::Right:
			controladora->getJugador()->setDireccion(EDireccion::Derecha);
			break;
		}
	}
	private: System::Void TeclaKeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		default:
			controladora->getJugador()->setDireccion(EDireccion::Ninguna);
			break;
		}
	}
	};
}
