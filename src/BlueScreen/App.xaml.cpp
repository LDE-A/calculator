//
// App.xaml.cpp
// App クラスの実装。
//

#include "pch.h"
#include "DirectXPage.xaml.h"

using namespace BlueScreen;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
/// <summary>
/// 単一アプリケーション オブジェクトを初期化します。これは、実行される作成したコードの
///最初の行であるため、main() または WinMain() と論理的に等価です。
/// </summary>
App::App()
{
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
	Resuming += ref new EventHandler<Object^>(this, &App::OnResuming);
}

/// <summary>
/// アプリケーションがエンド ユーザーによって正常に起動されたときに呼び出されます。他のエントリ ポイントは、
/// アプリケーションが特定のファイルを開くために起動されたときに
/// 検索結果やその他の情報を表示するために使用されます。
/// </summary>
/// <param name="e">起動の要求とプロセスの詳細を表示します。</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
#if _DEBUG
	if (IsDebuggerPresent())
	{
		DebugSettings->EnableFrameRateCounter = true;
	}
#endif

	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// ウィンドウに既にコンテンツが表示されている場合は、アプリケーションの初期化を繰り返さずに、
	// ウィンドウがアクティブであることだけを確認してください
	if (rootFrame == nullptr)
	{
		// ナビゲーション コンテキストとして動作するフレームを作成し、
		// SuspensionManager キーに関連付けます
		rootFrame = ref new Frame();

		rootFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);

		// フレームを現在のウィンドウに配置します
		Window::Current->Content = rootFrame;
	}

	if (rootFrame->Content == nullptr)
	{
		// ナビゲーション スタックが復元されない場合は、最初のページに移動します。
		// このとき、必要な情報をナビゲーション パラメーターとして渡して、新しいページを
		//構成します
		rootFrame->Navigate(TypeName(DirectXPage::typeid), e->Arguments);
	}

	if (m_directXPage == nullptr)
	{
		m_directXPage = dynamic_cast<DirectXPage^>(rootFrame->Content);
	}

	if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
	{
		m_directXPage->LoadInternalState(ApplicationData::Current->LocalSettings->Values);
	}
	
	// 現在のウィンドウがアクティブであることを確認します
	Window::Current->Activate();
}
/// <summary>
/// アプリケーションの実行が中断されたときに呼び出されます。
/// アプリケーションが終了されるか、メモリの内容がそのままで再開されるかに
/// かかわらず、アプリケーションの状態が保存されます。
/// </summary>
/// <param name="sender">中断要求の送信元。</param>
/// <param name="e">中断要求の詳細。</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void) sender;	// 未使用のパラメーター
	(void) e;	// 未使用のパラメーター

	m_directXPage->SaveInternalState(ApplicationData::Current->LocalSettings->Values);
}

/// <summary>
/// アプリケーションの実行が再開されたときに呼び出されます。
/// </summary>
/// <param name="sender">再開要求の送信元。</param>
/// <param name="args">再開要求の詳細。</param>
void App::OnResuming(Object ^sender, Object ^args)
{
	(void) sender; // 未使用のパラメーター
	(void) args; // 未使用のパラメーター

	m_directXPage->LoadInternalState(ApplicationData::Current->LocalSettings->Values);
}

/// <summary>
/// 特定のページへの移動が失敗したときに呼び出されます
/// </summary>
/// <param name="sender">移動に失敗したフレーム</param>
/// <param name="e">ナビゲーション エラーの詳細</param>
void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
	throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}

